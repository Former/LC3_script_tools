#include "../gtest/gtest.h"

#include "vm.h"

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#define ARRAY_SWAP(data) do { for (size_t i = 0; i < ARRAY_SIZE(data); ++i) data[i] = LC3_SWAP(data[i]); } while(0)

TEST(LC3SIM_C, Create_Destroy)
{
    vm_ctx vm = vm_create();
    vm_destroy(vm);
}

TEST(LC3SIM_C, LoadOS)
{
    vm_ctx vm = vm_create();
    vm_load_result res = vm_load_os(vm);
    vm_destroy(vm);
    
    EXPECT_EQ(res, VM_LOAD_SUCCESS);
}

#ifdef LC3_32BIT
#   define BIG_DATA 0xFFFFFFu
#else
#   define BIG_DATA 0x1FFFu
#endif

TEST(LC3SIM_C, LoadDataNopOn0)
{
    lc3_register_type data[] = {0u, 0u, 0xFFu, BIG_DATA};
    
    ARRAY_SWAP(data);

    vm_ctx vm = vm_create();
    vm_load_result res = vm_load_data(vm, (const unsigned char*)data, sizeof(data));

    vm_byte out[3] = {1, 1, 1};
    vm_result res_read[3] = {VM_ERROR_ADDRES_OUT_OF_RANGE, VM_ERROR_ADDRES_OUT_OF_RANGE, VM_ERROR_ADDRES_OUT_OF_RANGE};

    for (int i = 0; i < 3; ++i)
        res_read[i] = vm_mem_read(vm, i, &out[i]);

    vm_destroy(vm);

    EXPECT_EQ(res_read[0], VM_SUCCESS);
    EXPECT_EQ(out[0], 0u);

    EXPECT_EQ(res_read[1], VM_SUCCESS);
    EXPECT_EQ(out[1], 0xFFu);

    EXPECT_EQ(res_read[2], VM_SUCCESS);
    EXPECT_EQ(out[2], BIG_DATA);

    EXPECT_EQ(res, VM_LOAD_SUCCESS);
}

TEST(LC3SIM_C, LoadDataNopOn100)
{
    lc3_register_type data[] = {100u, 0u, 0xFFu, BIG_DATA};
    
    ARRAY_SWAP(data);

    vm_ctx vm = vm_create();
    vm_load_result res = vm_load_data(vm, (const unsigned char*)data, sizeof(data));

    vm_byte out[3] = {1, 1, 1};
    vm_result res_read[3] = {VM_ERROR_ADDRES_OUT_OF_RANGE, VM_ERROR_ADDRES_OUT_OF_RANGE, VM_ERROR_ADDRES_OUT_OF_RANGE};

    for (int i = 0; i < 3; ++i)
        res_read[i] = vm_mem_read(vm, 100 + i, &out[i]);

    vm_destroy(vm);

    EXPECT_EQ(res_read[0], VM_SUCCESS);
    EXPECT_EQ(out[0], 0u);

    EXPECT_EQ(res_read[1], VM_SUCCESS);
    EXPECT_EQ(out[1], 0xFFu);

    EXPECT_EQ(res_read[2], VM_SUCCESS);
    EXPECT_EQ(out[2], BIG_DATA);

    EXPECT_EQ(res, VM_LOAD_SUCCESS);
}

TEST(LC3SIM_C, RunNopOn0)
{
    lc3_register_type data[] = {0u, 0u, 0xFFu, 0x13u};

    ARRAY_SWAP(data);

    vm_ctx vm = vm_create();
    vm_load_result res = vm_load_data(vm, (const unsigned char*)data, sizeof(data));

    vm_result res_run = vm_run(vm);

    vm_destroy(vm);

    EXPECT_EQ(res, VM_LOAD_SUCCESS);
    EXPECT_EQ(res_run, VM_OPCODE_NOP);
}

TEST(LC3SIM_C, RunNopOn100)
{
    lc3_register_type data[] = {100u, 0u, 0xFFu, 0x13u};

    ARRAY_SWAP(data);

    vm_ctx vm = vm_create();
    vm_load_result res = vm_load_data(vm, (const unsigned char*)data, sizeof(data));

    vm_result res_run = vm_run(vm);

    vm_destroy(vm);

    EXPECT_EQ(res, VM_LOAD_SUCCESS);
    EXPECT_EQ(res_run, VM_OPCODE_NOP);
}
