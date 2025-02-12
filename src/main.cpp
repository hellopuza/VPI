#include "vpi_user.h"
#include <cassert>

char const* get_full_name()
{
    s_vpi_vlog_info info;
    vpi_get_vlog_info(&info);
    assert(info.argc == 2);
    return info.argv[1];
}

PLI_INT32 callback(p_cb_data data)
{
}

void callback_register()
{
    s_cb_data data{
        .reason = cbStartOfSimulation,
        .cb_rtn = callback,
        .obj = nullptr,
        .time = nullptr,
        .value = nullptr,
        .index = 0,
        .user_data = nullptr,
    };
    vpiHandle handle = vpi_register_cb(&data);
    assert(handle);
    vpi_free_object(handle);
}

void (*vlog_startup_routines[])() = {
    callback_register,
    nullptr
};


