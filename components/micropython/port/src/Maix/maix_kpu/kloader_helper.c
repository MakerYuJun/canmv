#include <stdint.h>

#include <mp.h>
#include "vfs_wrapper.h"
#include "vfs_spiffs.h"
#include "aes.h"
#include <mpprint.h>

int load_file_from_flash(uint32_t addr, uint8_t *data_buf, uint32_t length){
    // w25qxx_init(3, 0, 25000000);
    //w25qxx_read_data(addr, data_buf, length);
    sys_spiffs_read(addr, length, data_buf);

    return 0;
}

int load_file_from_ff(const char *path, void* buffer, size_t model_size)
{
    int ret = 0;
    mp_obj_t fp;
    file_read_open_raise(&fp, path);
    if(read_data(fp, buffer, model_size))
    {
        ret = -2; //error
    }
    file_close(fp);

    return ret;
}

mp_uint_t get_file_size(const char *path)
{
    mp_obj_t fp;
    mp_uint_t size = 0;

    int err = file_read_open(&fp, path);
    if(fp == MP_OBJ_NULL || err != 0)
        mp_raise_ValueError("open file error, please check file path!");//mp_raise_OSError(err);
    size = file_size(fp);
    file_close(fp);
    return size;
}
