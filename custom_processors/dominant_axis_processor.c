// custom_processors/dominant_axis_processor.c

#define DT_DRV_COMPAT zmk_input_processor_dominant_axis

#include <zephyr/device.h>
#include <zmk/input/input_event.h>
#include <zmk/input/input_processor.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(dominant_axis, CONFIG_INPUT_PROCESSOR_LOG_LEVEL);

struct dominant_axis_config {};

struct dominant_axis_data {
    const struct device *dev;
};

static int dominant_axis_process(const struct device *dev, struct input_event *evt) {
    // X軸とY軸の移動量の絶対値を取得
    int32_t abs_dx = abs(evt->body.point.dx);
    int32_t abs_dy = abs(evt->body.point.dy);

    // X軸の移動量がY軸より大きい場合、Y軸の移動量を0にする
    if (abs_dx > abs_dy) {
        evt->body.point.dy = 0;
    } 
    // Y軸の移動量がX軸より大きい場合、X軸の移動量を0にする
    else if (abs_dy > abs_dx) {
        evt->body.point.dx = 0;
    }
    // 等しい場合は何もしない（斜め移動を許可）

    return 0; // イベントを次のプロセッサに渡す
}

static int dominant_axis_init(const struct device *dev) {
    struct dominant_axis_data *data = dev->data;
    data->dev = dev;
    return 0;
}

INPUT_PROCESSOR_DT_INST_DEFINE(0, dominant_axis_init, NULL,
                               struct dominant_axis_data,
                               &dominant_axis_config, APPLICATION,
                               CONFIG_INPUT_PROCESSOR_INIT_PRIORITY,
                               dominant_axis_process);
