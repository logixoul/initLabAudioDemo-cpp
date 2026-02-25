#pragma once
#include <variant>
#include "NoteManager.h"
#include <readerwriterqueue.h>

// Inter-thread Communication port. Similar to JavaScript's.
template<class THandler>
class ITCMessagePort {
    using MessageVariant = typename THandler::MessageVariant;
    moodycamel::ReaderWriterQueue<MessageVariant> mQueue;
    THandler* mHandler;
public:
    ITCMessagePort(THandler* handler) : mHandler(handler) {
    }

    // call this only from the producer thread
    void push(const MessageVariant& msg) {
        mQueue.enqueue(msg);
    }

    // call this only from the consumer thread.
    void handlePendingMessages() {
        MessageVariant msg;
        while (mQueue.try_dequeue(msg)) {
            std::visit(*mHandler, msg);
        }
    }
};