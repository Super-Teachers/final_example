#ifndef LOG_HPP_POXWAJK8
#define LOG_HPP_POXWAJK8

#include <iostream>
#include <thread>

#define LOG(a)                                                                 \
    std::cerr << __FILE__ << "@" << __LINE__ << "["                            \
              << std::this_thread::get_id() << "] " << a << std::endl;

#endif /* end of include guard: LOG_HPP_POXWAJK8 */
