/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/core/framework/common_shape_fns.h"
#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/shape_inference.h"

namespace tensorflow {

REGISTER_OP("TextInput")
    .Input("source: string")
    .Output("handle: variant")
    .Attr("filters: list(string) = []")
    .SetShapeFn([](shape_inference::InferenceContext* c) {
       c->set_output(0, c->MakeShape({c->UnknownDim()}));
       return Status::OK();
     });

REGISTER_OP("TextDataset")
    .Input("input: T")
    .Output("handle: variant")
    .Attr("output_types: list(type) >= 1")
    .Attr("output_shapes: list(shape) >= 1")
    .Attr("T: {string, variant} = DT_VARIANT")
    .SetIsStateful()
    .SetShapeFn([](shape_inference::InferenceContext* c) {
       c->set_output(0, c->MakeShape({}));
       return Status::OK();
     });

REGISTER_OP("TextOutputSequence")
    .Input("destination: string")
    .Output("sequence: resource")
    .Attr("container: string = ''")
    .Attr("shared_name: string = ''")
    .SetIsStateful()
    .SetShapeFn(shape_inference::ScalarShape);
REGISTER_OP("TextOutputSequenceSetItem")
    .Input("sequence: resource")
    .Input("index: int64")
    .Input("item: string")
    .SetIsStateful()
    .SetShapeFn(shape_inference::ScalarShape);

}  // namespace tensorflow