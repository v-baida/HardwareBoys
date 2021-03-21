# Embed the server root certificate into the final binary
#
# (If this was a component, we would set COMPONENT_EMBED_TXTFILES here.)
idf_component_register(SRCS "car_detector_main.c"
                            "HWDrivers/optoelectronic_sensor/optoelectronic_sensor.c"
                            "SWDrivers/object_detector/object_detector.c"
                    INCLUDE_DIRS "."
                                "HWDrivers/optoelectronic_sensor"
                                "SWDrivers/object_detector")