
if(APPLE)
       install(DIRECTORY camera memory DESTINATION muan/plugins COMPONENT files)
elseif(WIN32)
    install(DIRECTORY camera memory DESTINATION plugins COMPONENT files)
else()
	#install(DIRECTORY camera memory DESTINATION local/share/muan/plugins COMPONENT files)
    install(DIRECTORY camera memory DESTINATION share/muan/plugins COMPONENT files)
endif()


