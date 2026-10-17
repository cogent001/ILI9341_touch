file(GLOB SOURCES *.C)
set(include_dirs "."
"C:/Espressif/frameworks/esp-idf-v4.4.1/components/fatfs"
"C:/Espressif/frameworks/esp-idf-v4.4.1/components/fatfs/src"
"C:/Espressif/frameworks/esp-idf-v4.4.1/components/fatfs/vfs"
"C:/Espressif/frameworks/esp-idf-v4.4.1/components/wear_levelling/include"
"C:/Espressif/frameworks/esp-idf-v4.4.1/components/wear_levelling"
"C:/Espressif/frameworks/esp-idf-v4.4.1/components/sdmmc/include"
"C:/Espressif/frameworks/esp-idf-v4.4.1/components/sdmmc"
)
idf_component_register(SRCS ${SOURCES}
INCLUDE_DIRS .
"${include_dirs}"
REQUIRES lvgl__lvgl my_sd_fatfs)
