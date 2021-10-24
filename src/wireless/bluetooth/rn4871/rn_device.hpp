/********************************************************************************
 *  File Name:
 *    rn_device.hpp
 *
 *  Description:
 *    High level device interface to an RN4871
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef RN4871_DEVICE_HPP
#define RN4871_DEVICE_HPP

/* Chimera Includes */
#include <Chimera/serial>
#include <Chimera/thread>

/* Driver Includes */
#include <src/wireless/bluetooth/rn4871/rn_types.hpp>

namespace RN4871
{
  /*---------------------------------------------------------------------------
  Forward Declarations
  ---------------------------------------------------------------------------*/
  class DeviceDriver;

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  /**
   * @brief Starts the RN4871 device manager thread
   *
   * @param device                      Which device to act on
   * @param attr                        Optional thread attributes
   * @return Chimera::Thread::TaskId    ID of the created thread
   */
  Chimera::Thread::TaskId startDevice( DeviceDriver &device, const Chimera::Thread::TaskConfig *attr );

  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  class DeviceDriver
  {
  public:
    DeviceDriver();
    ~DeviceDriver();

    /*-------------------------------------------------------------------------
    Device Information
    -------------------------------------------------------------------------*/
    VersionString softwareVersion();
    int connectionStrength();
    bool isConnected();

    /*-------------------------------------------------------------------------
    General Configuration
    -------------------------------------------------------------------------*/
    /**
     * @brief Performs more complex class initialization
     *
     * @return true
     * @return false
     */
    bool initialize();

    /**
     * @brief Assigns the serial channel used to communicate with the module
     * @note The serial driver must already be initialized.
     *
     * @param channel     Which serial channel to use
     */
    void assignSerial( const Chimera::Serial::Channel channel );

    /**
     * @brief Assigns the name to the BT device
     *
     * @param name    Name to be assigned
     * @return true   Device accepted the name
     * @return false  Failure occurred
     */
    bool setName( const std::string_view &name );

    /**
     * @brief Sets the TX power during advertisement
     *
     * @param pwr       Power level to transmit at
     * @return bool
     */
    bool setAdvertisePower( const OutputPower pwr );

    /**
     * @brief Sets the TX power once connected to a device
     *
     * @param pwr       Power level to transmit at
     * @return bool
     */
    bool setConnectedPower( const OutputPower pwr );

    /**
     * @brief Sets the GAP service the device will identify as
     * See https://www.bluetooth.com/ for more information, or download the values from
     * https://specificationrefs.bluetooth.com/assigned-values/Appearance%20Values.pdf.
     *
     * @param service   Service ID to identify as
     * @return bool
     */
    bool setGAPService( const uint16_t service );

    /**
     * @brief Configure supported feature set
     *
     * @param bitmap      Feature set bitmap
     * @return true       Features were set
     * @return false      Features were not set
     */
    bool setFeatures( const Feature bitmap );

    /*-------------------------------------------------------------------------
    System Commands
    -------------------------------------------------------------------------*/
    /**
     * @brief Instructs the RN4871 to perform a warm reset
     * Will only return once the expected command sequence was observed
     *
     * @return true   Reboot process success
     * @return false  Reboot failed
     */
    bool reboot();

    /**
     * @brief Start advertisement of the device
     *
     * @return true   Advertisement started
     * @return false  Advertisement failed to start
     */
    bool startAdvertisement();

    /**
     * @brief Stop advertisement of the device
     *
     * @return true   Advertisement stopped
     * @return false  Advertisement still going
     */
    bool stopAdvertisement();

    /**
     * @brief Instructs the module to enter comand mode
     *
     * @return true   Command mode entered
     * @return false  Command mode not entered
     */
    bool enterCommandMode();

    /**
     * @brief Instructs the module to enter data mode
     *
     * @return true   Data mode entered
     * @return false  Data mode not entered
     */
    bool exitCommandMode();

    /*-------------------------------------------------------------------------
    Service Configuration Commands
    -------------------------------------------------------------------------*/
    bool clearServices();

    bool setCharacteristic( const DeviceCharacteristic &dc );

  protected:
    friend Chimera::Thread::TaskId startDevice( DeviceDriver &, const Chimera::Thread::TaskConfig * );

    Internal::ControlBlock dcb; /**< Device control block */

    /**
     * @brief Manager thread for the device
     *
     * @param arg   Unused
     */
    void run( void *arg );

  private:
    /**
     * @brief Auto-performs a full command communication cycle
     *
     * Handles transitioning the device to command mode and performing the full
     * transaction. This includes listening for the expected response as well as
     * performing any number of retries.
     *
     * @param command     Command to send
     * @param terminator  Expected valid response terminator
     * @param expected    Expected valid response string
     * @param retries     Number of retries to allow
     * @param timeout     Response timeout from the BT device
     * @return StatusCode
     */
    StatusCode doCommand( const PacketString &command, const std::string_view &terminator, const std::string_view &expected,
                          const size_t retries, const size_t timeout );

    /**
     * @brief Sends a string to the BT module
     *
     * @param cmd       Command to send
     * @return StatusCode
     */
    StatusCode transfer( const PacketString &cmd );

    /**
     * @brief Listens for a message from the BT module
     *
     * @param rsp         Where to write the response into
     * @param terminator  Expected termination string
     * @param timeout     How long to wait for the message
     * @return StatusCode Result of the accumulation
     */
    StatusCode accumulateResponse( PacketString &rsp, const std::string_view &terminator, const size_t timeout );

    void doTransactionalProcessing();

    void doPassthroughProcessing();
  };
}    // namespace RN4871

#endif /* !RN4871_DEVICE_HPP */
