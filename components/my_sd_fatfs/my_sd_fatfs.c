#include "my_sd_fatfs.h"

static const char *TAG = "TFCardFat";

#define MOUNT_POINT     "/sdcard" 		//  The first byte must be '/'
//#define SPI_DMA_CHAN    2

//When testing SD and SPI modes, remember that once the card is initialized in SPI mode, it cannot be reinitialized in SD mode without turning on the card power.
#define CONFIG_EXAMPLE_PIN_CMD  38
#define CONFIG_EXAMPLE_PIN_CLK  39
#define CONFIG_EXAMPLE_PIN_D0   40

//static void get_fatfs_usage(size_t* out_total_bytes, size_t* out_free_bytes);


void SD_Fatfs_Init(void)
{
	esp_err_t ret;								// ESP error definition
	sdmmc_card_t* card;							// SD / MMC card information structure
	const char mount_point[] = MOUNT_POINT;		// root directory
	char ReadFileBuff[64];

	esp_vfs_fat_sdmmc_mount_config_t mount_config = {	// File system mount configuration
		.format_if_mount_failed = false,				// If the mount fails: true will repartition and format / false will not repartition and format
		.max_files = 5,									// Maximum number of open files
		.allocation_unit_size = 16 * 1024
	};

	ESP_LOGI(TAG,"->Initializing SD card");
	ESP_LOGI(TAG,"->Using SDMMC peripheralr");
	sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
	slot_config.width = 1;
    slot_config.clk = CONFIG_EXAMPLE_PIN_CLK;
    slot_config.cmd = CONFIG_EXAMPLE_PIN_CMD;
    slot_config.d0 = CONFIG_EXAMPLE_PIN_D0;
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    /*
     sdmmc_host_t host = SDSPI_HOST_DEFAULT();
     spi_bus_config_t slot_config = {
		.mosi_io_num = PIN_NUM_MOSI,
		.miso_io_num = PIN_NUM_MISO,
		.sclk_io_num = PIN_NUM_CLK,
		.quadwp_io_num = -1,
		.quadhd_io_num = -1,
		.max_transfer_sz = 4 * 1024 * sizeof(uint8_t),
	};
    */

	//host.slot = 2;
	// SPI bus initialization
	//ret = spi_bus_initialize(host.slot, &bus_cfg, SPI_DMA_CHAN);
	//if (ret != ESP_OK) {
	//	printf("%s->Failed to initialize bus.\r\n",TAG);
	//	return;
	//}

    // Mount file system
    ESP_LOGI(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);
     if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                     "If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                     "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
        }
        return;
    }
    ESP_LOGI(TAG, "Filesystem mounted");
     // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);

	// This initializes slots without card detection (CD) and write protect (WP) signals.
	// If your motherboard has these signals, please modify the slot_config.gpio_cd and slot_config.gpio_wp. 
	//sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();// SPI2_HOST  1
	//slot_config.gpio_cs = PIN_NUM_CS;
	//slot_config.host_id = host.slot;
	// Mount file system
    /*
	ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);
	if (ret != ESP_OK) {
		if (ret == ESP_FAIL) {
			printf("%s->Failed to mount filesystem.%s\r\n",TAG,
				"If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
		} else {
			printf("%s->Failed to initialize the card %s  (%s). ",TAG,
				"Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
		}
		return;
	}
	// TF card has been initialized. Print TF Card properties
	sdmmc_card_print_info(stdout, card);
    */

	// Print FAT FS size information
	//size_t bytes_total, bytes_free;
	//get_fatfs_usage(&bytes_total, &bytes_free);
	//printf("%s->FAT FS Total: %d MB, Free: %d MB \r\n",TAG, bytes_total / 1024, bytes_free / 1024);
}
