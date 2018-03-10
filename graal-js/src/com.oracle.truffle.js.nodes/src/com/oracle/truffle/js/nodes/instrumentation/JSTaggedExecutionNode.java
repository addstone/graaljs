/*
 * Copyright (c) 2018, 2018, Oracle and/or its affiliates. All rights reserved.
 * ORACLE PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
 */
package com.oracle.truffle.js.nodes.instrumentation;

import com.oracle.truffle.api.frame.VirtualFrame;
import com.oracle.truffle.api.instrumentation.Tag;
import com.oracle.truffle.js.nodes.JavaScriptNode;

/**
 * A utility node used by the instrumentation framework to tag a given node with a specific tag. By
 * wrapping nodes with this class, tagging can be performed lazily, rather than at parsing time.
 *
 */
public final class JSTaggedExecutionNode extends JavaScriptNode {

    @Child private JavaScriptNode child;

    private final Class<? extends Tag> expectedTag;
    private final NodeObjectDescriptor descriptor;

    public static JavaScriptNode createFor(JavaScriptNode originalNode, Class<? extends Tag> expectedTag) {
        JavaScriptNode clone = cloneUninitialized(originalNode);
        JavaScriptNode wrapper = new JSTaggedExecutionNode(clone, expectedTag);
        wrapper.setSourceSection(originalNode.getSourceSection());
        return wrapper;
    }

    public static JavaScriptNode createFor(JavaScriptNode originalNode, Class<? extends Tag> expectedTag, NodeObjectDescriptor descriptor) {
        JavaScriptNode clone = cloneUninitialized(originalNode);
        JavaScriptNode wrapper = new JSTaggedExecutionNode(clone, expectedTag, descriptor);
        wrapper.setSourceSection(originalNode.getSourceSection());
        return wrapper;
    }

    private JSTaggedExecutionNode(JavaScriptNode child, Class<? extends Tag> expectedTag) {
        this(child, expectedTag, null);
    }

    public JSTaggedExecutionNode(JavaScriptNode child, Class<? extends Tag> expectedTag, NodeObjectDescriptor descriptor) {
        this.child = child;
        this.descriptor = descriptor;
        this.expectedTag = expectedTag;
    }

    @Override
    public Object getNodeObject() {
        if (descriptor != null) {
            return descriptor;
        }
        return child.getNodeObject();
    }

    @Override
    public boolean hasTag(Class<? extends Tag> tag) {
        if (tag == expectedTag) {
            return true;
        } else {
            return super.hasTag(tag);
        }
    }

    @Override
    public Object execute(VirtualFrame frame) {
        return child.execute(frame);
    }

    @Override
    protected JavaScriptNode copyUninitialized() {
        return new JSTaggedExecutionNode(cloneUninitialized(child), expectedTag);
    }
}
