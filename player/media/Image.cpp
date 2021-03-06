#include "Image.hpp"

#include "MediaVisitor.hpp"
#include "adaptors/IImageAdaptor.hpp"

#include <cassert>

Image::Image(int id, int width, int height, const FilePath& path, ImageProperties props, std::unique_ptr<IImageAdaptor>&& handler) :
    Media(id), m_handler(std::move(handler)), m_scaleType(props.scaleType), m_align(props.align), m_valign(props.valign)
{
    assert(m_handler);

    m_handler->setSize(width, height);
    loadImage(path);
}

void Image::show()
{
    m_handler->show();
}

void Image::hide()
{
    m_handler->hide();
}

void Image::loadImage(const FilePath& path)
{
    bool preserveAspectRatio = (m_scaleType == ImageProperties::ScaleType::Scaled) ? true : false;
    m_handler->loadImage(path, preserveAspectRatio);
}

int Image::width() const
{
    return m_handler->width();
}

int Image::height() const
{
    return m_handler->height();
}

void Image::scale(double scaleX, double scaleY)
{
    m_handler->scale(scaleX, scaleY);
}

IWidgetAdaptor& Image::handler()
{
    return *m_handler;
}

void Image::apply(MediaVisitor& visitor)
{
    visitor.visit(*this);
}

void Image::handleEvent(const Event& ev)
{
    switch(ev.type())
    {
        case EventType::StartMedia:
            show();
            break;
        case EventType::StopMedia:
            hide();
            break;
        case EventType::ScaleMedia:
        {
            auto scaleEv = static_cast<const ScaleMediaEvent&>(ev);
            scale(scaleEv.scaleX(), scaleEv.scaleY());
            break;
        }
        default:
            break;
    }
}

ImageProperties::ScaleType Image::scaleType() const
{
    return m_scaleType;
}

ImageProperties::Align Image::align() const
{
    return m_align;
}

ImageProperties::Valign Image::valign() const
{
    return m_valign;
}
