#ifndef SUBSCRIPTIONCALLBACKDOUBLE_H
#define SUBSCRIPTIONCALLBACKDOUBLE_H

class SubscriptionCallbackDouble {
  public:
    virtual void handle(const int mode, const double value) = 0;  
};

#endif
