#include <vector>
#include "gpio.cpp"

class Controller
{
public:
    Controller(std::vector<Gpio*> lights)
    {
        this->_lights = lights;
    }

    void open(int index){
        _lights[index]->gpio_set_value(1);
    }

    void close(int index)
    {
        _lights[index]->gpio_set_value(0);
    }

    void openAllLights()
    {
        for(int i = 0 ;i<_lights.size();i++)
        {
            this->open(i);
        }
    }

    void closeAllLights()
    {
        for(int i = 0 ;i<_lights.size();i++)
        {
            this->close(i);
        }
    }
    void unexportAllLight()
    {
        for(int i = 0 ;i<_lights.size();i++)
        {
            delete _lights[i];
        }
    }

private:
    std::vector<Gpio*> _lights;

};
