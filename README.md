# Dynamic Loading vs Static Compiled Performance Tests

> Answering a question that no one usually asks

[![Build Status](https://travis-ci.org/HedenEnterprises/dynamic-loading-perftests.svg?branch=main)](https://travis-ci.org/HedenEnterprises/dynamic-loading-perftests)

## Initial Results

Well, you can look and see what the function does in module.c. We call this function - either from a statically compiled function pointer, or a function pointer that looks up the function via `dlsym`.
