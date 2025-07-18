/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 * Copyright (c) 2015 Runtime Inc
 * Copyright (c) 2020 Embedded Planet
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the Licens
 */

#ifndef H_UTIL_FLASH_MAP_
 #define H_UTIL_FLASH_MAP_

 #ifdef __cplusplus
extern "C" {
 #endif

/**
 *
 * Provides abstraction of flash regions for type of use.
 * I.e. dude where's my image?
 *
 * System will contain a map which contains flash areas. Every
 * region will contain flash identifier, offset within flash and length.
 *
 * 1. This system map could be in a file within filesystem (Initializer
 * must know/figure out where the filesystem is at).
 * 2. Map could be at fixed location for project (compiled to code)
 * 3. Map could be at specific place in flash (put in place at mfg time).
 *
 * Note that the map you use must be valid for BSP it's for,
 * match the linker scripts when platform executes from flash,
 * and match the target offset specified in download script.
 */
 #include <inttypes.h>

/**
 * @brief Structure describing an area on a flash device.
 *
 * Multiple flash devices may be available in the system, each of
 * which may have its own areas. For this reason, flash areas track
 * which flash device they are part of.
 */
struct flash_area
{
    /**
     * This flash area's ID; unique in the system.
     */
    uint8_t fa_id;

    /**
     * ID of the flash device this area is a part of.
     */
    uint8_t fa_device_id;

    uint16_t pad16;

    /**
     * This area's offset, relative to the beginning of its flash
     * device's storage.
     */
    uint32_t fa_off;

    /**
     * This area's size, in bytes.
     */
    uint32_t fa_size;
};
static inline uint8_t flash_area_get_id (const struct flash_area * fa)
{
    return fa->fa_id;
}

static inline uint8_t flash_area_get_device_id (const struct flash_area * fa)
{
    return fa->fa_device_id;
}

static inline uint32_t flash_area_get_off (const struct flash_area * fa)
{
    return fa->fa_off;
}

static inline uint32_t flash_area_get_size (const struct flash_area * fa)
{
    return fa->fa_size;
}

/**
 * @brief Structure describing a sector within a flash area.
 *
 * Each sector has an offset relative to the start of its flash area
 * (NOT relative to the start of its flash device), and a size. A
 * flash area may contain sectors with different sizes.
 */
struct flash_sector
{
    /**
     * Offset of this sector, from the start of its flash area (not device).
     */
    uint32_t fs_off;

    /**
     * Size of this sector, in bytes.
     */
    uint32_t fs_size;
};

static inline uint32_t flash_sector_get_off (const struct flash_sector * fs)
{
    return fs->fs_off;
}

static inline uint32_t flash_sector_get_size (const struct flash_sector * fs)
{
    return fs->fs_size;
}

struct flash_map_entry
{
    uint32_t          magic;
    struct flash_area area;
    unsigned int      ref_count;
};

/*
 * Retrieve a memory-mapped flash device's base address.
 * On success, the address will be stored in the value pointed to by
 * ret.
 * Returns 0 on success, or an error code on failure.
 */
int flash_device_base(uint8_t fd_id, uintptr_t * ret);

/* Initialiaze all flash driver */
int flash_area_driver_init(void);

/*< Opens the area for use. id is one of the `fa_id`s */
int  flash_area_open(uint8_t id, const struct flash_area ** area);
void flash_area_close(const struct flash_area * area);

/*
 * Read/write/erase. Offset is relative from beginning of flash area.
 */
int flash_area_read(const struct flash_area * area, uint32_t off, void * dst, uint32_t len);
int flash_area_write(const struct flash_area * area, uint32_t off, const void * src, uint32_t len);
int flash_area_erase(const struct flash_area * area, uint32_t off, uint32_t len);

/*
 * Alignment restriction for flash writes.
 */
uint32_t flash_area_align(const struct flash_area * area);

/*
 * What is value is read from erased flash bytes.
 */
uint8_t flash_area_erased_val(const struct flash_area * area);

/*
 * Given flash area ID, return info about sectors within the area.
 */
int flash_area_get_sectors(int fa_id, uint32_t * count, struct flash_sector * sectors);

int flash_area_id_from_image_slot(int slot);
int flash_area_id_from_multi_image_slot(int image_index, int slot);

int flash_area_id_to_image_slot(int area_id);

/**
 * Converts the specified flash area ID and image index (in multi-image setup)
 * to an image slot index.
 *
 * Returns image slot index (0 or 1), or -1 if ID doesn't correspond to an image
 * slot.
 */
int flash_area_id_to_multi_image_slot(int image_index, int area_id);

int rm_mcuboot_cleanup(void);

/*
 * Clean up on chip flash driver.
 */
int flash_on_chip_cleanup(void);

typedef struct rm_mcuboot_port_flush_buffer
{
    uint32_t   g_current_block;
    uint32_t * p_flush_buffer;
} rm_mcuboot_port_flush_buffer_t;

/*
 * Flush on chip flash buffer.
 */
int flash_on_chip_flush(const struct flash_area * area);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* H_UTIL_FLASH_MAP_ */
