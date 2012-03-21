
set(FcstdThumbnailer_SRCS fcstdcreator.cpp)

kde4_add_plugin(fcstdthumbnailer ${FcstdThumbnailer_SRCS})

target_link_libraries(fcstdthumbnailer ${KDE4_KIO_LIBS} )

install(TARGETS fcstdthumbnailer DESTINATION ${PLUGIN_INSTALL_DIR} )

install(FILES  fcstdthumbnailer.desktop DESTINATION ${SERVICES_INSTALL_DIR})
