include_directories(${server_client_SOURCE_DIR}/include)

add_library(src 
    entities/Client.cpp
    entities/Entity.cpp
    entities/Server.cpp
    receiver/TextReceiver.cpp
    receiver/FileReceiver.cpp
    sender/TextSender.cpp
    sender/FileSender.cpp
    streamDownload/VidStreamDownload.cpp
    streamUpload/VidStreamUpload.cpp
    utils.cpp
    main.cpp
)
