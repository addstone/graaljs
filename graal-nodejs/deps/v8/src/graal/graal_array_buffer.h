/*
 * Copyright (c) 2018, 2021, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * The Universal Permissive License (UPL), Version 1.0
 *
 * Subject to the condition set forth below, permission is hereby granted to any
 * person obtaining a copy of this software, associated documentation and/or
 * data (collectively the "Software"), free of charge and under any and all
 * copyright rights in the Software, and any and all patent rights owned or
 * freely licensable by each licensor hereunder covering either (i) the
 * unmodified Software as contributed to or provided by such licensor, or (ii)
 * the Larger Works (as defined below), to deal in both
 *
 * (a) the Software, and
 *
 * (b) any piece of software and/or hardware listed in the lrgrwrks.txt file if
 * one is included with the Software each a "Larger Work" to which the Software
 * is contributed by such licensors),
 *
 * without restriction, including without limitation the rights to copy, create
 * derivative works of, display, perform, and distribute the Software and make,
 * use, sell, offer for sale, import, export, have made, and have sold the
 * Software and the Larger Work(s), and to sublicense the foregoing rights on
 * either these or other terms.
 *
 * This license is subject to the following condition:
 *
 * The above copyright notice and either this complete permission notice or at a
 * minimum a reference to the UPL must be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef GRAAL_ARRAY_BUFFER_H_
#define GRAAL_ARRAY_BUFFER_H_

#include "graal_object.h"

class GraalIsolate;

class GraalArrayBuffer : public GraalObject {
public:
    inline static GraalArrayBuffer* Allocate(GraalIsolate* isolate, jobject java_array_buffer, bool direct);
    inline static GraalArrayBuffer* Allocate(GraalIsolate* isolate, jobject java_array_buffer, bool direct, void* placement);
    size_t ByteLength() const;
    bool IsArrayBuffer() const;
    bool IsDirect() const;
    bool IsExternal() const;
    void Detach();
    std::shared_ptr<v8::BackingStore> GetBackingStore();
    static v8::Local<v8::ArrayBuffer> New(v8::Isolate* isolate, size_t byte_length);
    static v8::Local<v8::ArrayBuffer> New(v8::Isolate* isolate, void* data, size_t byte_length, v8::ArrayBufferCreationMode mode);
    static v8::Local<v8::ArrayBuffer> New(v8::Isolate* isolate, std::shared_ptr<v8::BackingStore> backing_store);
protected:
    inline GraalArrayBuffer(GraalIsolate* isolate, jobject java_array_buffer, bool direct);
    GraalHandleContent* CopyImpl(jobject java_object_copy) override;
    inline void Recycle() override {
        delete this;
    }
private:
    bool direct_;
};

#endif /* GRAAL_ARRAY_BUFFER_H_ */
