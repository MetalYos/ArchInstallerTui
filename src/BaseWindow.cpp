#include <BaseWindow.hpp>

BaseWindow::BaseWindow(int id, PubSub& pubsub, const std::string& title)
    : id(id), pubsub(pubsub), title(title)
{

}

void BaseWindow::SetPosition(int y, int x) {
    this->y = y;
    this->x = x;
    Refresh();
}

void BaseWindow::SetSize(int width, int height) {
    this->height = height;
    this->width = width;
    Refresh();
}

void BaseWindow::SetTitle(const std::string& title) {
    this->title = title;
    Refresh();
}

int BaseWindow::GetId() const {
    return id;
}

void BaseWindow::Refresh() {
    wrefresh(window);
}

void BaseWindow::PrintInMiddle(WINDOW *win, int startY, int startX, int width, const std::string& str) {
    int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startX != 0)
		x = startX;
	if(startY != 0)
		y = startY;
	if(width == 0)
		width = 80;

	length = str.length();
	temp = (width - length)/ 2;
	x = startX + (int)temp;
	mvwprintw(win, y, x, "%s", str.c_str());
	refresh();
}

