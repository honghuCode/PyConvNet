#ifndef PYCONVNET_CONVOLUTION_LAYER_HPP
#define PYCONVNET_CONVOLUTION_LAYER_HPP

#include <vector>
#include "Tensor.hpp"
#include "Layer.hpp"

class ConvolutionLayer: public Layer {
public:
    ConvolutionLayer(const int pad_h_, const int pad_w_,
                     const int filter_num, const int filter_channel,
                        const int kernel_h_, const int kernel_w_,
                        const int stride_h_, const int stride_w_):
            filter(filter_num, filter_channel, kernel_h_, kernel_w_, 0.01),
            bias(filter_num, 1, 1, 1),
            d_filter(filter_num, filter_channel, kernel_h_, kernel_w_),
            d_bias(filter_num, 1, 1, 1),
            pre_update_f(filter_num, filter_channel, kernel_h_, kernel_w_),
            pre_update_b(filter_num, 1, 1, 1) {
        pad_h = pad_h_;
        pad_w = pad_w_;
        kernel_h = kernel_h_;
        kernel_w = kernel_w_;
        stride_h = stride_h_;
        stride_w = stride_w_;

    };
    // set_* function is used while testing layer
    void set_filter(Tensor& f) {
        filter = f;
    };
    void set_bias(Tensor& b) {
        bias = b;
    };
    void set_d_filter(Tensor& d_f) {
        d_filter = d_f;
    };
    void set_d_bias(Tensor& d_b) {
        d_bias = d_b;
    };

    void forward(std::vector<Tensor>& input, std::vector<Tensor>& output );
    void backward(std::vector<Tensor>& input,
                  std::vector<Tensor>& output);
    void params_update(float lr);

private:
    Tensor filter;
    Tensor bias;
    Tensor d_filter;
    Tensor pre_update_f;
    Tensor d_bias;
    Tensor pre_update_b;
    int pad_h = 0;
    int pad_w = 0;
    int kernel_h = 0;
    int kernel_w = 0;
    int stride_h = 0;
    int stride_w = 0;
};
#endif //PYCONVNET_CONVOLUTION_LAYER_HPP
