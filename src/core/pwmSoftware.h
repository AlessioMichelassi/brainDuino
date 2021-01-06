class pwmSoftware
{
private:
    int counter = 0;
    int onTime = 1;
    int offTime = 1;
    int maxTime = 100;
    int signal = 1;

public:
    pwmSoftware(/* args */);
    ~pwmSoftware();
    int returnPwm();
};

pwmSoftware::pwmSoftware(/* args */)
{
}

pwmSoftware::~pwmSoftware()
{
}

