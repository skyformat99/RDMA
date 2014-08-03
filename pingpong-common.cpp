#include "pingping-common.h"

void query_device() {
	struct ibv_context *ctx;
	struct ibv_device **device_list;
	struct ibv_device_attr device_attr;
	int device_num;

	device_list = ibv_get_device_list(&device_num);
	if (!device_list) {
		throw std::runtime_error("ibv_get_device_list failed!");
	}

	//We open the first device
	ctx = ibv_open_device(device_list[0]);
	if (!ctx) {
		throw std::runtime_error("ibv_open_device failed!");
	}

	if (ibv_query_device(ctx, &device_attr)) {
		throw std::runtime_error("ibv_query_device failed!");
	}

	printf("The device '%s' max mr size is %u bytes. around %lf GBytes.\n",
			ibv_get_device_name(ctx->device), device_attr.max_mr_size,
			(long long)device_attr.max_mr_size / (1024.0 * 1024 * 1024));

	printf("There are %d devices!\n", device_num);

	ibv_close_device(ctx);
	ibv_free_device_list(device_list);
}