#include "generator.h"
#include "../realtime.h"
#include "objutils.h"
#include "staticposdata.h"

// TODO: CHANGE THESE
#define CITY_KA 0.3f
#define CITY_KD 0.7f
#define CITY_KS 0.5f

void CopiedCity::GenerateCity() {

    // clear city data
    CopiedCity::city.cityData.clear();

    // global constant data
    CopiedCity::city.globals.ka = CITY_KA;
    CopiedCity::city.globals.kd = CITY_KD;
    CopiedCity::city.globals.ks = CITY_KS;

    // set singular cube trimesh
    CopiedCity::city.cube = new Cube(); // TODO: remember to destroy this!
    CopiedCity::city.cube->UpdateParams(settings.shapeParameter1, settings.shapeParameter2); // set tesselation parameters to build the cube

    // generate the bottom plane
    CopiedCity::city.GeneratePlane();

    // then generate the left and right facades
    CopiedCity::city.GenerateFacades();

    // generate the lights
    CopiedCity::city.GenerateLights();
}



void CopiedCityData::GeneratePlane() {
    CopiedCityData::plane.planeData = CityMeshObject{};
    // initialize CTM and inv transpose CTM
    InitializeSpaceConversions(&CopiedCityData::plane.planeData, &PLANE);

    // initialize material
    InitializeMaterial(&CopiedCityData::plane.planeData, &PLANE);

//    // initialize object tesselation DONT NEED BECAUSE USE SAME CUBE
//    CopiedCityData::plane.planeData.trimesh = new Cube();
//    CopiedCityData::plane.planeData.trimesh->UpdateParams(settings.shapeParameter1, settings.shapeParameter2);

    CopiedCityData::cityData.emplace_back(&CopiedCityData::plane.planeData);
}
// more stuff goes here about potential details on the bottom of the plane



void CopiedCityData::GenerateFacades() {

    // TODO: call city facade's functions to generate/populate the necessary mesh objects

    auto leftF = CityMeshObject{};

    // initialize CTM and inv transpose CTM
    InitializeSpaceConversions(&leftF, &LEFTFACADEPLACE);

    // initialize material
    InitializeMaterial(&leftF, &LEFTFACADEPLACE);

    auto rightF = CityMeshObject{};

    // initialize CTM and inv transpose CTM
    InitializeSpaceConversions(&rightF, &RIGHTFACADEPLACE);

    // initialize material
    InitializeMaterial(&rightF, &RIGHTFACADEPLACE);

    auto backF = CityMeshObject{};

    // initialize CTM and inv transpose CTM
    InitializeSpaceConversions(&backF, &BACKFACADEPLACE);

    // initialize material
    InitializeMaterial(&backF, &BACKFACADEPLACE);


    CopiedCityData::leftFacade.data.emplace_back(leftF);
    CopiedCityData::rightFacade.data.emplace_back(rightF);
    CopiedCityData::leftFacade.data.emplace_back(backF);
}


void CopiedCityData::GenerateLights() {
    // add lights
    SceneLightData directionalLightL = {.id = 0, .type = LightType::LIGHT_DIRECTIONAL, .color = SceneColor(1.f,1.f,1.f,1.f),
                                       .function = glm::vec3(1.f,0.f,0.f), .pos = glm::vec4(3.f,3.f,3.f,1.f),
                                        .dir = glm::normalize(glm::vec4(-0.7f,-1.f, 0.5f, 0.f)),
                                       .penumbra = 0.f, .angle = 0.f, .width =0, .height = 0};

    SceneLightData directionalLightR = {.id = 0, .type = LightType::LIGHT_DIRECTIONAL, .color = SceneColor(1.f,1.f,1.f,1.f),
                                       .function = glm::vec3(1.f,0.f,0.f), .pos = glm::vec4(3.f,3.f,3.f,1.f),
                                        .dir = glm::normalize(glm::vec4(0.7f,-1.f, 0.5f, 0.f)),
                                       .penumbra = 0.f, .angle = 0.f, .width =0, .height = 0};
    CopiedCityData::lights.emplace_back(directionalLightL);
    CopiedCityData::lights.emplace_back(directionalLightR);
}




