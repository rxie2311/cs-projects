#ifndef ROAD_H
#define ROAD_H

// C++ Libraries
#include <string>

// Road Class
class Road {
public:
    // Constructor
    Road() = default;

    // GET methods
    virtual std::string getName() const = 0;
    virtual std::string getDesc() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getTraffic() const = 0;
    virtual int getDelay() const = 0;
    virtual int getPopHour() const = 0;
    virtual bool getConstruction() const = 0;
    virtual int getRoadID() const = 0;

    // SET methods
    virtual void setName(const std::string& newName) = 0;
    virtual void setDesc(const std::string& newDesc) = 0;
    virtual void setTraffic(const std::string& newTraffic) = 0;
    virtual void setDelay(int newDelay) = 0;
    virtual void setPopHour(int newPopHour) = 0;
    virtual void setConstruction(bool newConstruction) = 0;
    virtual void setRoadID(int newRoadID) = 0;
};

// Concrete Class - Local Road
class Local : public Road {
public:
    // Constructor
    Local(const std::string& name, const std::string& desc, const std::string& traffic, int delay, int popHour, bool construction, int roadID);

    // GET methods
    std::string getName() const override;
    std::string getDesc() const override;
    std::string getType() const override;
    std::string getTraffic() const override;
    int getDelay() const override;
    int getPopHour() const override;
    bool getConstruction() const override;
    int getRoadID() const override;

    // SET methods
    void setName(const std::string& newName) override;
    void setDesc(const std::string& newDesc) override;
    void setTraffic(const std::string& newTraffic) override;
    void setDelay(int newDelay) override;
    void setPopHour(int newPopHour) override;
    void setConstruction(bool newConstruction) override;
    void setRoadID(int newRoadID) override;

private:
    // Instance variables
    std::string name;
    std::string desc;
    std::string traffic;
    int delay;
    int popHour;
    bool construction;
    int roadID;
};

// Concrete Class - Highway
class Highway : public Road {
public:
    // Constructor
    Highway(const std::string& name, const std::string& desc, const std::string& traffic, int delay, int popHour, bool construction, int roadID);

    // GET methods
    std::string getName() const override;
    std::string getDesc() const override;
    std::string getType() const override;
    std::string getTraffic() const override;
    int getDelay() const override;
    int getPopHour() const override;
    bool getConstruction() const override;
    int getRoadID() const override;

    // SET methods
    void setName(const std::string& newName) override;
    void setDesc(const std::string& newDesc) override;
    void setTraffic(const std::string& newTraffic) override;
    void setDelay(int newDelay) override;
    void setPopHour(int newPopHour) override;
    void setConstruction(bool newConstruction) override;
    void setRoadID(int newRoadID) override;

private:
    // Instance variables
    std::string name;
    std::string desc;
    std::string traffic;
    int delay;
    int popHour;
    bool construction;
    int roadID;
};

#endif // ROAD_H
