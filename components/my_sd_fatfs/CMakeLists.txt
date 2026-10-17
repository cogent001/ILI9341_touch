set(mysrcs "my_sd_fatfs.c")

idf_component_register(SRCS "${mysrcs}"
                       INCLUDE_DIRS "include"
					   REQUIRES fatfs)