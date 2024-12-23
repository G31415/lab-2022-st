#include <stdio.h>
#include "../common/common.h"
#define COLOR_BACKGROUND	FB_COLOR(0xff,0xff,0xff)
static int touch_fd;
int r = 35;
int last_x [5] = {-1};
int last_y [5] = {-1};
int color[5] =
{
    FB_COLOR(65,105,225),   //Blue
    FB_COLOR(0,255,127),    //Spring Green
    FB_COLOR(255,215,0),    //Gold
    FB_COLOR(255,140,0),    //Dark Orange
    FB_COLOR(255,69,0)     //Orange Red
};

void draw_plate(int x0, int y0, int r, int color)
{
    if (r <= 0) return;  // 半径为0不绘制
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;  // 初始偏移量
    // 处理八个对称点，并填充每一行
    while (x <= y) {
        // 绘制每一行的所有像素（填充效果）
        for (int i = x0 - x; i <= x0 + x; i++) {
            fb_draw_pixel(i, y0 + y, color);  // 顶部半圆
            fb_draw_pixel(i, y0 - y, color);  // 底部半圆
        }
        for (int i = x0 - y; i <= x0 + y; i++) {
            fb_draw_pixel(i, y0 + x, color);  // 左侧半圆
            fb_draw_pixel(i, y0 - x, color);  // 右侧半圆
        }
        x++;  // 增加x
        if (p < 0) {
            p = p + 4 * x + 6;  // 决策参数小于零时，选择东向
        } else {
            p = p + 4 * (x - y) + 10;  // 决策参数大于等于零时，选择东南向
            y--;  // 减少y
        }
    }
}
static void touch_event_cb(int fd)
{
	int type,x,y,finger;
	type = touch_read(fd, &x,&y,&finger);
	switch(type){
	case TOUCH_PRESS:
		printf("TOUCH_PRESS：x=%d,y=%d,finger=%d,color=%d\n",x,y,finger,color[finger]);
        draw_plate(x,y,r,color[finger]);
        last_x[finger] = x;
        last_y[finger] = y;
        fb_update();
        break;
	case TOUCH_MOVE:
	    printf("TOUCH_MOVE：x=%d,y=%d,finger=%d,color=%d\n", x,y,finger,color[finger]);
	    draw_plate (last_x[finger],last_y[finger],r,COLOR_BACKGROUND);
		draw_plate (x,y,r,color[finger]);
            last_x[finger] = x;
            last_y[finger] = y;
            fb_update();
        break;
	case TOUCH_RELEASE:
		printf("TOUCH_RELEASE：x=%d,y=%d,finger=%d\n",x,y,finger);
		draw_plate(last_x[finger],last_y[finger],r,COLOR_BACKGROUND);
		last_x[finger] = -1;
		last_y[finger] = -1;
        fb_update();
		break;
	case TOUCH_ERROR:
		printf("close touch fd\n");
		close(fd);
		task_delete_file(fd);
		break;
	default:
		return;
	}
	fb_update();
	return;
}

int main(int argc, char *argv[])
{
	fb_init("/dev/fb0");
	fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,COLOR_BACKGROUND);
	fb_update();

	//打开多点触摸设备文件, 返回文件fd
	touch_fd = touch_init("/dev/input/event1");
	//添加任务, 当touch_fd文件可读时, 会自动调用touch_event_cb函数
	task_add_file(touch_fd, touch_event_cb);
	
	task_loop(); //进入任务循环
	return 0;
}
