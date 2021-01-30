/********************************************************************************
 *  File Name:
 *    tsk_graphics.cpp
 *
 *  Description:
 *    Implementation of the file system thread
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/interrupt>
#include <Chimera/serial>
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_file_system.hpp>


// TEMPORARY FOR TESTING
#include <Aurora/database>

static Aurora::Database::RAMDB db;
static Aurora::Database::EntryStore<15> dbEntryStore;
static std::array<uint8_t, 1024> dbRAM;

static constexpr uint32_t test_key_1 = 1520;
static constexpr uint32_t test_key_2 = 2458;

static const std::string_view test_data_1 = "This is some test data\r\n";
static const float test_data_2 = 3.1459f;


namespace DC::Tasks::FIL
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void FileSystemThread( void *arg )
  {
    using namespace Chimera::Threading;
    using namespace Chimera::Interrupt;
    using namespace Chimera::Peripheral;

    /*-------------------------------------------------
    Wait for initialization command
    -------------------------------------------------*/
    this_thread::pendTaskMsg( ITCMsg::TSK_MSG_WAKEUP, TIMEOUT_BLOCK );
    Chimera::delayMilliseconds( 500 );

    /*-------------------------------------------------
    Test out the database
    -------------------------------------------------*/
    db.assignCoreMemory( dbEntryStore, dbRAM.data(), dbRAM.size() );
    db.reset();

    db.insert( test_key_1, test_data_1.data(), test_data_1.size(), Aurora::Database::MemAccess::MEM_RW );
    db.insert( test_key_2, &test_data_2, sizeof( test_data_2), Aurora::Database::MemAccess::MEM_RW );


    std::array<char, 45> result_data_1;
    result_data_1.fill( 0 );

    float result_data_2 = 0.0f;

    bool readResult1 = db.read( test_key_1, result_data_1.data() );
    bool readResult2 = db.read( test_key_2, &result_data_2 );


    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();

      Chimera::delayMilliseconds( lastWoken, 100 );
    }
  }
}    // namespace DC::Tasks::FIL
