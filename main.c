#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iup.h>
#include "zmper.h"

int exit_cb(void)
{
    return IUP_CLOSE;
}

int about_cb(void)
{
    IupMessage("关于", "by lzw-723\n仅供学习交流，请勿用于非法用途！");
    return IUP_CONTINUE;
}

int faq_cb(void)
{
	IupMessage("常见问题", "Q1:如何打开隐藏的压缩包？\nA1:改图片文件后缀为压缩包后缀，如.zip\n\nQ2:为什么别人无法打开隐藏的压缩包？\nA2:请确定图片文件未经压缩或裁剪");
}

char path_pic[512];
int select_pic_cb(Ihandle *self)
{
    Ihandle *label_pic = IupGetDialogChild(self, "LABEL_PIC");
    char path[512] = "/*.gif;*.jpg;*.png;*.bmp";
    int status = IupGetFile(path);
    if(status != -1) {
        strcpy(path_pic, path);
        IupSetAttribute(label_pic, "TITLE", path_pic);
    }

    return IUP_CONTINUE;
}

char path_file[512];
int select_file_cb(Ihandle *self)
{
    Ihandle *label_file = IupGetDialogChild(self, "LABEL_FILE");
    char path[512] = "/*.zip;*.zipx;*.rar;*.7z";
    int status = IupGetFile(path);
    if(status != -1) {
        strcpy(path_file, path);
        IupSetAttribute(label_file, "TITLE", path_file);
    }
    return IUP_CONTINUE;
}

char path_dir_finish[512];
int merge_cb(Ihandle *self)
{
    if(path_pic != NULL && path_file != NULL && strlen(path_pic) > 0 && strlen(path_file) > 0) {
    	
    	char path[512] = "/*.gif;*.jpg;*.png;*.bmp";
    	if(IupGetFile(path) == -1){
    		return;
		}
    	strcpy(path_dir_finish, path);
//    	IupMessage("a", path_dir_finish);
        FILE *f_pic = open(path_pic, "rb");
        FILE *f_file = open(path_file, "rb");
        FILE *f_finish = open(path_dir_finish, "wb");
        merge(f_pic, f_file, f_finish);
        char t[1024];
        sprintf(t, "合并%s与%s成功！\n输出文件位于%s", path_pic, path_file, path_dir_finish);
        IupMessage("合并结果", t);
    }
    else {
    	IupMessage("提示", "请先选择文件！");
	}
	return IUP_CONTINUE;
}

int reset_cb(Ihandle *self) {
	strcpy(path_pic, "");
	strcpy(path_file, "");
	Ihandle *label_pic = IupGetDialogChild(self, "LABEL_PIC");
	Ihandle *label_file = IupGetDialogChild(self, "LABEL_FILE");
	IupSetAttribute(label_pic, "TITLE", "未选择");
	IupSetAttribute(label_file, "TITLE", "未选择");
	IupMessage("重置", "重置成功！");
	return IUP_CONTINUE;
}

void load_menu(Ihandle *dlg)
{
    Ihandle *setting_menu, *item_exit, *help_menu, *item_about, *item_faq;
    Ihandle *sub1_menu, *sub2_menu, *menu;
    item_exit = IupItem("退出", NULL);
    IupSetCallback(item_exit, "ACTION", (Icallback)exit_cb);
    setting_menu = IupMenu(item_exit, NULL);
    sub1_menu = IupSubmenu("设置", setting_menu);

    item_about = IupItem("关于", NULL);
    IupSetCallback(item_about, "ACTION", (Icallback)about_cb);
    item_faq = IupItem("常见问题", NULL);
    IupSetCallback(item_faq, "ACTION", (Icallback)faq_cb);
    help_menu = IupMenu(item_faq, item_about, NULL);
    sub2_menu = IupSubmenu("帮助", help_menu);

    menu = IupMenu(sub1_menu, sub2_menu, NULL);
    IupSetAttributeHandle(dlg, "MENU", menu);
}

int main(int argc, char **argv)
{

    Ihandle *dlg, *label_pic, *label_file, *btn_pic, *btn_file, *btn_reset, *btn_merge, *hbox, *vbox_label, *vbox_select;


    IupOpen(&argc, &argv);

    label_pic = IupLabel("未选择");
    IupSetAttribute(label_pic, "EXPAND", "YES");
    IupSetAttribute(label_pic, "NAME", "LABEL_PIC");
    label_file = IupLabel("未选择");
    IupSetAttribute(label_file, "EXPAND", "YES");
    IupSetAttribute(label_file, "NAME", "LABEL_FILE");
    vbox_label = IupVbox(label_pic, label_file, NULL);
    IupSetAttribute(vbox_label, "ALIGNMENT", "ACENTER");
    IupSetAttribute(vbox_label, "GAP", "10");
    IupSetAttribute(vbox_label, "MARGIN", "10x10");
//    IupSetAttribute(vbox_label, "EXPANDCHILDREN", "YES");

    btn_pic = IupButton("选择图片", NULL);
    IupSetCallback(btn_pic, "ACTION", (Icallback)select_pic_cb);
    btn_file = IupButton("选择压缩包", NULL);
    IupSetCallback(btn_file, "ACTION", (Icallback)select_file_cb);
    vbox_select = IupVbox(btn_pic, btn_file, NULL);
    IupSetAttribute(vbox_select, "ALIGNMENT", "ACENTER");
    IupSetAttribute(vbox_select, "GAP", "10");
    IupSetAttribute(vbox_select, "MARGIN", "10x10");
//    IupSetAttribute(vbox_select, "EXPANDCHILDREN", "YES");

    btn_merge = IupButton("合并", NULL);
    IupSetCallback(btn_merge, "ACTION", (Icallback)merge_cb);
    btn_reset = IupButton("重置", NULL);
    IupSetCallback(btn_reset, "ACTION", (Icallback)reset_cb);
    hbox = IupHbox(vbox_label, vbox_select, btn_merge, btn_reset, NULL);
    IupSetAttribute(hbox, "ALIGNMENT", "ACENTER");
    IupSetAttribute(hbox, "GAP", "10");
    IupSetAttribute(hbox, "MARGIN", "10x10");
//    IupSetAttribute(hbox, "EXPANDCHILDREN", "YES");

    dlg = IupDialog(hbox);

    IupSetAttribute(dlg, "TITLE", "ZPMer");
    IupSetAttribute(dlg, "SIZE", "QUARTERxQUARTER");

    load_menu(dlg);

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupSetAttribute(dlg, "USERSIZE", NULL);

    IupMainLoop();

    IupClose();
    return EXIT_SUCCESS;
}