include_directories(${server_client_SOURCE_DIR}/include)

add_library(src 
    entities/Client.cpp
    entities/Entity.cpp
    entities/Server.cpp
    receiver/TextReceiver.cpp
    receiver/FileReceiver.cpp
    sender/FileSender.cpp
    sender/TextSender.cpp
    sender/SenderFactory.cpp
    streamDownload/VidStreamDownload.cpp
    streamUpload/VidStreamUpload.cpp
    UDPPacket/UDPPacket.cpp
    utils.cpp
    main.cpp
)
