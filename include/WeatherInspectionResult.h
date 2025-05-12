#ifndef WeatherInspectionResult_H
#define WeatherInspectionResult_H


class WeatherInspectionResult{
protected:
    bool isVisibility;
    bool isHorizontalVisibility;
    bool isCrosswind;
    bool isTemperature;
    bool isThunderstorm;
    bool isTailwind;
    bool inspectionResult ;
public:
    WeatherInspectionResult();
    WeatherInspectionResult(bool isVisibility,bool isHorizontalVisibility, bool isCrosswind, bool isTailw, bool isTemperature, bool isThunderstorm);
    //Getters
    bool getIsVisibility() const;
    bool getIsCrosswind() const;
    bool getIsTemperature() const;
    bool getIsThunderstorm() const;
    bool getIsTailwind() const;
    bool getIsHorizontalVisibility() const;
    bool getInspectionResult() const;
    //Setters
    void setIsVisibility(bool isVisibility);
    void setIsCrosswind(bool isCrosswind);
    void setIsTemperature(bool isTemperature);
    void setIsThunderstorm(bool isThunderstorm);
    void setIsTailwind(bool isTailwind);
    void setIsHorizontalVisibility(bool isHorizontalVisibility);
    void setInspectionResult(bool inspectionResult);

};

#endif