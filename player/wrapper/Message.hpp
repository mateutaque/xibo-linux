#pragma once

#include <string>
#include <gst/gst.h>

namespace Gst
{
    enum class MessageType
    {
      UNKNOWN = GST_MESSAGE_UNKNOWN,
      EOS = GST_MESSAGE_EOS,
      ERROR = GST_MESSAGE_ERROR,
      WARNING = GST_MESSAGE_WARNING,
      INFO = GST_MESSAGE_INFO,
      TAG = GST_MESSAGE_TAG,
      BUFFERING = GST_MESSAGE_BUFFERING,
      STATE_CHANGED = GST_MESSAGE_STATE_CHANGED,
      STATE_DIRTY = GST_MESSAGE_STATE_DIRTY,
      STEP_DONE = GST_MESSAGE_STEP_DONE,
      CLOCK_PROVIDE = GST_MESSAGE_CLOCK_PROVIDE,
      CLOCK_LOST = GST_MESSAGE_CLOCK_LOST,
      NEW_CLOCK = GST_MESSAGE_NEW_CLOCK,
      STRUCTURE_CHANGE = GST_MESSAGE_STRUCTURE_CHANGE,
      STREAM_STATUS = GST_MESSAGE_STREAM_STATUS,
      APPLICATION = GST_MESSAGE_APPLICATION,
      ELEMENT = GST_MESSAGE_ELEMENT,
      SEGMENT_START = GST_MESSAGE_SEGMENT_START,
      SEGMENT_DONE = GST_MESSAGE_SEGMENT_DONE,
      DURATION_CHANGED = GST_MESSAGE_DURATION_CHANGED,
      LATENCY = GST_MESSAGE_LATENCY,
      ASYNC_START = GST_MESSAGE_ASYNC_START,
      ASYNC_DONE = GST_MESSAGE_ASYNC_DONE,
      REQUEST_STATE = GST_MESSAGE_REQUEST_STATE,
      STEP_START = GST_MESSAGE_STEP_START,
      QOS = GST_MESSAGE_QOS,
      PROGRESS = GST_MESSAGE_PROGRESS,
      TOC = GST_MESSAGE_TOC,
      RESET_TIME = GST_MESSAGE_RESET_TIME,
      STREAM_START = GST_MESSAGE_STREAM_START,
      NEED_CONTEXT = GST_MESSAGE_NEED_CONTEXT,
      HAVE_CONTEXT = GST_MESSAGE_HAVE_CONTEXT,
      EXTENDED = GST_MESSAGE_EXTENDED,
      DEVICE_ADDED = GST_MESSAGE_DEVICE_ADDED,
      DEVICE_REMOVED = GST_MESSAGE_DEVICE_REMOVED,
#if GST_CHECK_VERSION(1,10,0)
      PROPERTY_NOTIFY = GST_MESSAGE_PROPERTY_NOTIFY,
      STREAM_COLLECTION = GST_MESSAGE_STREAM_COLLECTION,
      STREAMS_SELECTED = GST_MESSAGE_STREAMS_SELECTED,
      REDIRECT = GST_MESSAGE_REDIRECT,
#endif
      ANY = GST_MESSAGE_ANY
    };

    class MessageError
    {
    public:
        MessageError(const std::string& text, const std::string& debugInfo);
        const std::string& getText() const;
        const std::string& getDebugInfo() const;

    private:
        std::string m_text;
        std::string m_debugInfo;
    };

    class Message
    {
    public:
        Message(GstMessage* handler, bool takeOwnership = true);
        Gst::MessageError parseError();
        Gst::MessageType type() const;

    private:
        GstMessage* m_handler;
        bool m_takeOwnership;

    };
}
