#pragma once

#include "Media.hpp"
#include <gtkmm/image.h>

class Image : public Media
{
public:
    Image(const std::string& fileName);

    void init(MyRegion* region, const Point& pos, const Size& size, int zindex) override;
    void hide() override;
    void show() override;
    std::string get_filename() const;

private:
    Gtk::Image m_handler;
    std::string m_filename;

};