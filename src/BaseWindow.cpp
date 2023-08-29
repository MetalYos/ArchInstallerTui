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

