include_directories(${server_client_SOURCE_DIR}/include)

add_library(src 
    entities/Client.cpp
    entities/Entity.cpp
    entities/Server.cpp
    utils.cpp
    main.cpp
)