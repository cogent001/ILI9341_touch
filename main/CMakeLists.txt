# Edit following two lines to set component requirements (see docs)
file(GLOB_RECURSE IMAGE_SOURCES images/*.c)

set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS  
    "main.c"
    UI/grid.c
    UI/lv_example_menu_5.c
    UI/lvgl_UI.c
    ${IMAGE_SOURCES}
)

set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()
