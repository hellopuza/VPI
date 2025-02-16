#include <vpi_user.h>
#include <cstdlib>
#include <cstring>

#define assert(err) \
    if (!(err)) { vpi_printf("Assertion " #err " failed!\n"); exit(-1); }

static char const*
get_full_name()
{
    s_vpi_vlog_info info;
    assert(
        vpi_get_vlog_info(&info));
    assert(
        info.argc == 2);

    return info.argv[1];
}

static void
find_instances(vpiHandle module_handle, char const* module_name)
{
    vpiHandle iter_handle = vpi_iterate(vpiModule, module_handle);
    if (!iter_handle)
    {
        // No submodules!
        return;
    }

    vpiHandle submodule_handle;
    while ((submodule_handle = vpi_scan(iter_handle)) != NULL)
    {
        char* def_name = vpi_get_str(vpiDefName, submodule_handle);
        if (!strcmp(def_name, module_name))
        {
            vpi_printf("%s ", vpi_get_str(vpiFullName, submodule_handle));
            vpi_printf("%s\n", vpi_get_str(vpiType, submodule_handle));
        }

        find_instances(submodule_handle, module_name);
        assert(
            vpi_free_object(submodule_handle));
    }
}

static PLI_INT32
callback(p_cb_data)
{
    char const* module_name = get_full_name();

    vpiHandle iter_handle = vpi_iterate(vpiModule, NULL);
    if (!iter_handle)
    {
        vpi_printf("No modules found!\n");
        vpi_control(vpiFinish, 0);
        return -1;
    }

    vpiHandle module_handle;
    while ((module_handle = vpi_scan(iter_handle)) != NULL)
    {
        // Iterate through top modules and find instances
        find_instances(module_handle, module_name);
        assert(
            vpi_free_object(module_handle));
    }

    vpi_control(vpiFinish, 0);
    return 0;
}

static void
callback_register()
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
