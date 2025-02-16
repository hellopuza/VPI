#include <vpi_user.h>
#include <stdlib.h>

#define assert(err) \
    if (!(err)) { vpi_printf("Assertion " #err " failed!\n"); exit(-1); }

char const* get_full_name()
{
    s_vpi_vlog_info info;
    assert(
        vpi_get_vlog_info(&info));
    assert(
        info.argc == 2);

    return info.argv[1];
}

PLI_INT32 callback(p_cb_data)
{
    char const* full_name = get_full_name();
    vpi_printf("%s\n", full_name);

    vpiHandle module_handle;
    assert(
        module_handle = vpi_handle_by_name(full_name, NULL));

    vpi_control(vpiFinish, 0);
    return 0;
}

void callback_register()
{
    s_cb_data data{
        .reason = cbStartOfSimulation,
        .cb_rtn = callback,
        .obj = 0,
        .time = 0,
        .value = 0,
        .index = 0,
        .user_data = 0,
    };

    vpiHandle handle;
    assert(
        handle = vpi_register_cb(&data));
    assert(
        vpi_free_object(handle));
}

void (*vlog_startup_routines[])() = {
    callback_register,
    0
};
