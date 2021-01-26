# Details

Date : 2021-01-25 19:58:30

Directory /home/braunbr/git/Projects/DroneController/lib/Ripple

Total : 46 files,  3654 codes, 2861 comments, 1184 blanks, all 7699 lines

[summary](results.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [lib/Ripple/.clang-format](/lib/Ripple/.clang-format) | YAML | 73 | 0 | 3 | 76 |
| [lib/Ripple/README.md](/lib/Ripple/README.md) | Markdown | 5 | 0 | 2 | 7 |
| [lib/Ripple/doc/architecture.md](/lib/Ripple/doc/architecture.md) | Markdown | 47 | 0 | 14 | 61 |
| [lib/Ripple/doc/brainstorm.md](/lib/Ripple/doc/brainstorm.md) | Markdown | 16 | 0 | 7 | 23 |
| [lib/Ripple/doc/features_and_tasks.md](/lib/Ripple/doc/features_and_tasks.md) | Markdown | 5 | 0 | 2 | 7 |
| [lib/Ripple/doc/pipe_allocation.md](/lib/Ripple/doc/pipe_allocation.md) | Markdown | 29 | 0 | 8 | 37 |
| [lib/Ripple/inc/Ripple/network](/lib/Ripple/inc/Ripple/network) | C++ | 5 | 9 | 4 | 18 |
| [lib/Ripple/inc/Ripple/physical](/lib/Ripple/inc/Ripple/physical) | C++ | 9 | 9 | 4 | 22 |
| [lib/Ripple/inc/Ripple/session](/lib/Ripple/inc/Ripple/session) | C++ | 6 | 9 | 4 | 19 |
| [lib/Ripple/inc/Ripple/shared](/lib/Ripple/inc/Ripple/shared) | C++ | 6 | 9 | 4 | 19 |
| [lib/Ripple/inc/Ripple/transport](/lib/Ripple/inc/Ripple/transport) | C++ | 6 | 9 | 4 | 19 |
| [lib/Ripple/src/datalink/data_link_arp.cpp](/lib/Ripple/src/datalink/data_link_arp.cpp) | C++ | 59 | 26 | 23 | 108 |
| [lib/Ripple/src/datalink/data_link_arp.hpp](/lib/Ripple/src/datalink/data_link_arp.hpp) | C++ | 29 | 54 | 16 | 99 |
| [lib/Ripple/src/datalink/data_link_driver.cpp](/lib/Ripple/src/datalink/data_link_driver.cpp) | C++ | 18 | 13 | 5 | 36 |
| [lib/Ripple/src/datalink/data_link_driver.hpp](/lib/Ripple/src/datalink/data_link_driver.hpp) | C++ | 10 | 19 | 6 | 35 |
| [lib/Ripple/src/datalink/data_link_service.cpp](/lib/Ripple/src/datalink/data_link_service.cpp) | C++ | 359 | 240 | 111 | 710 |
| [lib/Ripple/src/datalink/data_link_service.hpp](/lib/Ripple/src/datalink/data_link_service.hpp) | C++ | 61 | 153 | 33 | 247 |
| [lib/Ripple/src/datalink/data_link_types.hpp](/lib/Ripple/src/datalink/data_link_types.hpp) | C++ | 91 | 78 | 27 | 196 |
| [lib/Ripple/src/network/network_thread.cpp](/lib/Ripple/src/network/network_thread.cpp) | C++ | 0 | 0 | 1 | 1 |
| [lib/Ripple/src/network/network_types.hpp](/lib/Ripple/src/network/network_types.hpp) | C++ | 31 | 44 | 17 | 92 |
| [lib/Ripple/src/physical/phy_device_constants.hpp](/lib/Ripple/src/physical/phy_device_constants.hpp) | C++ | 21 | 20 | 9 | 50 |
| [lib/Ripple/src/physical/phy_device_driver.cpp](/lib/Ripple/src/physical/phy_device_driver.cpp) | C++ | 976 | 482 | 277 | 1,735 |
| [lib/Ripple/src/physical/phy_device_driver.hpp](/lib/Ripple/src/physical/phy_device_driver.hpp) | C++ | 62 | 411 | 61 | 534 |
| [lib/Ripple/src/physical/phy_device_internal.cpp](/lib/Ripple/src/physical/phy_device_internal.cpp) | C++ | 164 | 75 | 48 | 287 |
| [lib/Ripple/src/physical/phy_device_internal.hpp](/lib/Ripple/src/physical/phy_device_internal.hpp) | C++ | 25 | 130 | 20 | 175 |
| [lib/Ripple/src/physical/phy_device_register.hpp](/lib/Ripple/src/physical/phy_device_register.hpp) | C++ | 260 | 67 | 23 | 350 |
| [lib/Ripple/src/physical/phy_device_types.hpp](/lib/Ripple/src/physical/phy_device_types.hpp) | C++ | 214 | 71 | 40 | 325 |
| [lib/Ripple/src/physical/phy_fsm_controller.cpp](/lib/Ripple/src/physical/phy_fsm_controller.cpp) | C++ | 202 | 64 | 66 | 332 |
| [lib/Ripple/src/physical/phy_fsm_controller.hpp](/lib/Ripple/src/physical/phy_fsm_controller.hpp) | C++ | 98 | 87 | 36 | 221 |
| [lib/Ripple/src/session/process/process_establish_connection.cpp](/lib/Ripple/src/session/process/process_establish_connection.cpp) | C++ | 29 | 13 | 17 | 59 |
| [lib/Ripple/src/session/process/process_intf.hpp](/lib/Ripple/src/session/process/process_intf.hpp) | C++ | 44 | 13 | 13 | 70 |
| [lib/Ripple/src/session/process/process_join_network.cpp](/lib/Ripple/src/session/process/process_join_network.cpp) | C++ | 29 | 14 | 18 | 61 |
| [lib/Ripple/src/session/process/process_terminate_connection.cpp](/lib/Ripple/src/session/process/process_terminate_connection.cpp) | C++ | 29 | 13 | 17 | 59 |
| [lib/Ripple/src/session/session_process.hpp](/lib/Ripple/src/session/session_process.hpp) | C++ | 46 | 61 | 19 | 126 |
| [lib/Ripple/src/session/session_service.cpp](/lib/Ripple/src/session/session_service.cpp) | C++ | 127 | 69 | 37 | 233 |
| [lib/Ripple/src/session/session_service.hpp](/lib/Ripple/src/session/session_service.hpp) | C++ | 40 | 89 | 22 | 151 |
| [lib/Ripple/src/session/session_types.hpp](/lib/Ripple/src/session/session_types.hpp) | C++ | 79 | 59 | 18 | 156 |
| [lib/Ripple/src/session/session_user.hpp](/lib/Ripple/src/session/session_user.hpp) | C++ | 18 | 83 | 15 | 116 |
| [lib/Ripple/src/shared/cmn_memory_config.hpp](/lib/Ripple/src/shared/cmn_memory_config.hpp) | C++ | 47 | 80 | 18 | 145 |
| [lib/Ripple/src/shared/cmn_types.hpp](/lib/Ripple/src/shared/cmn_types.hpp) | C++ | 9 | 10 | 6 | 25 |
| [lib/Ripple/src/shared/cmn_utils.cpp](/lib/Ripple/src/shared/cmn_utils.cpp) | C++ | 24 | 15 | 7 | 46 |
| [lib/Ripple/src/shared/cmn_utils.hpp](/lib/Ripple/src/shared/cmn_utils.hpp) | C++ | 13 | 29 | 8 | 50 |
| [lib/Ripple/src/transport/transport_service.cpp](/lib/Ripple/src/transport/transport_service.cpp) | C++ | 127 | 78 | 45 | 250 |
| [lib/Ripple/src/transport/transport_service.hpp](/lib/Ripple/src/transport/transport_service.hpp) | C++ | 44 | 108 | 25 | 177 |
| [lib/Ripple/src/transport/transport_types.hpp](/lib/Ripple/src/transport/transport_types.hpp) | C++ | 50 | 31 | 19 | 100 |
| [lib/Ripple/src/version.hpp](/lib/Ripple/src/version.hpp) | C++ | 12 | 17 | 5 | 34 |

[summary](results.md)