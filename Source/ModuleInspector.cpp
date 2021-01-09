#include "Globals.h"
#include "Application.h"
#include "ModuleInspector.h"
#include "ModuleGeometryManager.h"
#include "ModuleMeshImporter.h"
#include "ModuleEditor.h"

#include "Component.h"
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"
#include "ComponentListener.h"
#include "ComponentSource.h"
#include "ModuleScene.h"
#include "ModuleCamera3D.h"

#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"

#include "libraries/mmgr/mmgr.h"




ModuleInspectorGameObject::ModuleInspectorGameObject(Application* app, const char* name, bool start_enabled) : Module(app, name, start_enabled)
{
}

ModuleInspectorGameObject::~ModuleInspectorGameObject()
{}


bool ModuleInspectorGameObject::Start()
{
  

	return true;
}

update_status ModuleInspectorGameObject::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleInspectorGameObject::CleanUp()
{
	return true;
}

void ModuleInspectorGameObject::DrawInspectorWindowInfo()
{
	if (App->editor->show_inspector_window)
	{
		ImGui::Begin("Inspector", &App->editor->show_inspector_window);

		bool SomethingDrawn = false; // if there isnt an object in the list or if none of them

		//has ToBeDrawInspector==true we print a message saying theres nothing to draw

		Game_Object* ItemToDraw;
		for (std::vector<Game_Object*>::iterator IteratorLoaded = App->geometrymanager->ObjectsOnScene.begin(); IteratorLoaded != App->geometrymanager->ObjectsOnScene.end(); ++IteratorLoaded) {

			ItemToDraw = *IteratorLoaded;

			if (ItemToDraw->ToBeDrawInspector == true) {

				Component_Mesh* MeshComp = (Component_Mesh*)ItemToDraw->GetComponent(Component_Types::Mesh);
				Component_Texture* TexComp = (Component_Texture*)ItemToDraw->GetComponent(Component_Types::Texture);
				Component_Transform* TransComp = (Component_Transform*)ItemToDraw->GetComponent(Component_Types::Transform);
                Component_Camera* CamComp = (Component_Camera*)ItemToDraw->GetComponent(Component_Types::Camera);
                Component_Listener* ListComp = (Component_Listener*)ItemToDraw->GetComponent(Component_Types::Listener);
                Component_Source* SourceComp = (Component_Source*)ItemToDraw->GetComponent(Component_Types::Source);

				SomethingDrawn = true;
				DrawObjectInfo(ItemToDraw, MeshComp, TexComp, TransComp, CamComp, ListComp, SourceComp);
			}
			else if (ItemToDraw->Children_List.size() > 0) {

				Game_Object* ChildFoundDraw;
				std::vector<Game_Object*>::iterator ChildIteratorLoaded = ItemToDraw->Children_List.begin();
				for (int itB = 0; itB < ItemToDraw->Children_List.size(); ++itB) {

					ChildFoundDraw = *ChildIteratorLoaded;

                    SomethingDrawn=LookForChildrenToBeDrawn(ChildFoundDraw);
                    ++ChildIteratorLoaded;

					
				}
			}
		}

		

		ImGui::End();
	}
}

bool ModuleInspectorGameObject::LookForChildrenToBeDrawn(Game_Object* item)
{

    bool SomethingDrawn = false;

        if (item->ToBeDrawInspector) {

            Component_Mesh* MeshComp = (Component_Mesh*)item->GetComponent(Component_Types::Mesh);
            Component_Texture* TexComp = (Component_Texture*)item->GetComponent(Component_Types::Texture);
            Component_Transform* TransComp = (Component_Transform*)item->GetComponent(Component_Types::Transform);
            Component_Camera* CamComp = (Component_Camera*)item->GetComponent(Component_Types::Camera);
            Component_Listener* ListComp = (Component_Listener*)item->GetComponent(Component_Types::Listener);
            Component_Source* SourceComp = (Component_Source*)item->GetComponent(Component_Types::Source);

            SomethingDrawn = true;
            DrawObjectInfo(item, MeshComp, TexComp, TransComp, CamComp, ListComp, SourceComp);
        }
        else if (item->Children_List.size() > 0) {

            Game_Object* ChildFoundDraw;
            std::vector<Game_Object*>::iterator ChildIteratorLoaded = item->Children_List.begin();
            for (int itB = 0; itB < item->Children_List.size(); ++itB) {

                ChildFoundDraw = *ChildIteratorLoaded;

                if (ChildFoundDraw->ToBeDrawInspector == true) {

                    Component_Mesh* MeshComp2 = (Component_Mesh*)ChildFoundDraw->GetComponent(Component_Types::Mesh);
                    Component_Texture* TexComp2 = (Component_Texture*)ChildFoundDraw->GetComponent(Component_Types::Texture);
                    Component_Transform* TransComp2 = (Component_Transform*)ChildFoundDraw->GetComponent(Component_Types::Transform);
                    Component_Camera* CamComp2 = (Component_Camera*)ChildFoundDraw->GetComponent(Component_Types::Camera);
                    Component_Listener* ListComp2 = (Component_Listener*)ChildFoundDraw->GetComponent(Component_Types::Listener);
                    Component_Source* SourceComp2 = (Component_Source*)ChildFoundDraw->GetComponent(Component_Types::Source);

                    SomethingDrawn = true;

                    DrawObjectInfo(ChildFoundDraw, MeshComp2, TexComp2, TransComp2, CamComp2, ListComp2, SourceComp2);

                    itB = item->Children_List.size();
                }
                else {

                    SomethingDrawn = LookForChildrenToBeDrawn(ChildFoundDraw);

                    ++ChildIteratorLoaded;
                }
            }
        }

    
        return SomethingDrawn;
}

void ModuleInspectorGameObject::EqualizeSpatialObjScale(Game_Object* Object,Component_Transform* TransInfo)
{
    float MaxScale;
    float NewSpatialSize;

    Game_Object* SpatialObj = Object->Children_List[0]; //Change this if multiple childs


    if (SpatialObj->isAudioDistanceObject) {

        if (TransInfo->Scale.x < TransInfo->Scale.y) {

            if (TransInfo->Scale.y < TransInfo->Scale.z) {
                MaxScale = TransInfo->Scale.z;
            }
            else  if (TransInfo->Scale.y > TransInfo->Scale.z) {
                MaxScale = TransInfo->Scale.y;
            }
            else {
                MaxScale = TransInfo->Scale.y;
            }

        }
        else if (TransInfo->Scale.x > TransInfo->Scale.y) {

            if (TransInfo->Scale.x < TransInfo->Scale.z) {
                MaxScale = TransInfo->Scale.z;
            }
            else  if (TransInfo->Scale.x > TransInfo->Scale.z) {
                MaxScale = TransInfo->Scale.x;
            }
            else {
                MaxScale = TransInfo->Scale.x;
            }

        }
        else {

            if (TransInfo->Scale.x < TransInfo->Scale.z) {
                MaxScale = TransInfo->Scale.z;
            }
            else  if (TransInfo->Scale.x > TransInfo->Scale.z) {
                MaxScale = TransInfo->Scale.x;
            }
            else {
                MaxScale = TransInfo->Scale.x;
            }
        }

        Component_Transform* TransCompSpat = (Component_Transform*)SpatialObj->GetComponent(Component_Types::Transform);


        

        NewSpatialSize= TransCompSpat->Scale.x/MaxScale;


        TransCompSpat->Scale.x = NewSpatialSize;
        TransCompSpat->Scale.y = NewSpatialSize;
        TransCompSpat->Scale.z = NewSpatialSize;


        TransCompSpat->UpdateTransformationsObjects(TransCompSpat->Translation, TransCompSpat->Scale, TransCompSpat->Rotation);


    }




}

void ModuleInspectorGameObject::DrawObjectInfo(Game_Object* item, Component_Mesh* MeshInfo, Component_Texture* TextureInfo, Component_Transform* TransInfo, Component_Camera* CameraInfo, Component_Listener* ListInfo, Component_Source* SourceInfo)
{
    const char* Name;
    Name = item->name.c_str();

    if (MeshInfo != nullptr && MeshInfo->is_Drawn)
    {
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS, 1, -1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        item->Mesh->DrawOutlineMesh(TransInfo);
    }

    
    ImGui::Text(Name);
    
    ImGui::Text("%d", item->item_id);
   
        //GENERAL INFORMATION
    
        if (ImGui::CollapsingHeader("General Information", ImGuiTreeNodeFlags_DefaultOpen))
        {
            int ChildAmount;

            ImGui::InputText(" ", (char*)item->name.c_str(), 100, ImGuiInputTextFlags_EnterReturnsTrue);

            ImGui::Text("Child Amount  %d", ChildAmount = item->Children_List.size());

            ImGui::Text("Currently Textured:");

            if (TextureInfo != nullptr && TextureInfo->is_Textured == true) {

                ImGui::Text("True");
            }
            else {
                ImGui::Text("False");
            }

            if (MeshInfo != nullptr)
            {
                ImGui::Checkbox("Wireframed", &item->is_Wireframed);
            }
            
            if (MeshInfo != nullptr)
            {
                ImGui::Checkbox("Draw", &MeshInfo->is_Drawn);
            }

            else if (CameraInfo != nullptr)
            {
               ImGui::Checkbox("Activate", &CameraInfo->camera_drawn);
               ImGui::Checkbox("Camera Culling", &App->scene->camera_culling);
               ImGui::Checkbox("Reset Camera", &App->camera->reset_camera);
            }
            
            ImGui::Text("Item Id:");
            ImGui::SameLine(0.0f, 10.0f);
            ImGui::Text("%d", item->item_id);

            int CmpCount = 0;

            if (MeshInfo != nullptr) {
                ++CmpCount;
            }
            if (TextureInfo != nullptr) {
                ++CmpCount;
            }
            if (CameraInfo != nullptr) {
                ++CmpCount;
            }
            if (TransInfo != nullptr) {
                ++CmpCount;
            }

            ImGui::Text("Amount of Components: %d", CmpCount);


            ImGui::Separator();
        }

        if (TransInfo != nullptr && MeshInfo!=nullptr)
        {

            ///TRANSFORMATIONS
            if (ImGui::CollapsingHeader("Transformation", ImGuiTreeNodeFlags_DefaultOpen)) {


                if (ImGui::DragFloat3("Position", { &TransInfo->Translation.x }, 2)) {
                    TransInfo->UpdateTransformationsObjects(TransInfo->Translation, TransInfo->Scale, TransInfo->Rotation);

                    if (MeshInfo != nullptr)
                    {
                        MeshInfo->UpdateOnTransformOBB();
                    }
                    if (MeshInfo == nullptr)
                    {
                        CameraInfo->FrustumUpdateTransform(TransInfo->GetGlobalTransform());
                    }
                    
                }


                float3 DisplayVecRot = TransInfo->Rotation.ToEulerXYZ();

                if (ImGui::DragFloat3("Rotation", { &TransInfo->EulerRot.x }, 2)) {

                    Quat NewRot = Quat::FromEulerXYZ(TransInfo->EulerRot.x, TransInfo->EulerRot.y, TransInfo->EulerRot.z);

                    TransInfo->SetEulerRotation(TransInfo->EulerRot);

                    if (MeshInfo != nullptr)
                    {
                        MeshInfo->UpdateOnTransformOBB();
                    }

                    if (MeshInfo == nullptr)
                    {
                        CameraInfo->FrustumUpdateTransform(TransInfo->GetGlobalTransform());
                    }
                    
                }
                //This crashes if >0.01f
                if (ImGui::DragFloat3("Scale", { &TransInfo->Scale.x }, 2.0f, 0.0f)) {

                    float ScaleToSpatialObjectConversion;
                    if (TransInfo->Scale.x < 0.1)
                    {
                        TransInfo->Scale.x = 0.1;
                    }
                    if (TransInfo->Scale.y < 0.1)
                    {
                        TransInfo->Scale.y = 0.1;
                    }
                    if (TransInfo->Scale.z < 0.1)
                    {
                        TransInfo->Scale.z = 0.1;
                    }

                    //EqualizeSpatialObjScale(item, TransInfo);

                    


                    TransInfo->UpdateTransformationsObjects(TransInfo->Translation, TransInfo->Scale, TransInfo->Rotation);

                    if (MeshInfo != nullptr)
                    {
                        MeshInfo->UpdateOnTransformOBB();
                    }

                    if (MeshInfo == nullptr)
                    {
                        CameraInfo->FrustumUpdateTransform(TransInfo->GetGlobalTransform());
                    }
                    
                }

                ImGui::Separator();
            }
        }


        if (MeshInfo != nullptr)
        {
            //MESH INFO
            if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen)) {

                ImGui::Text("Index Amount:");
                ImGui::SameLine(0.0f, 10.0f);
                ImGui::Text("%d", MeshInfo->Mesh->num_index);

                ImGui::Text("Vertex Amount:");
                ImGui::SameLine(0.0f, 10.0f);
                ImGui::Text("%d", MeshInfo->Mesh->num_vertex);

                ImGui::Text("Id Index:");
                ImGui::SameLine(0.0f, 10.0f);
                ImGui::Text("%d", MeshInfo->Mesh->id_index);

                ImGui::Text("Id Vertex:");
                ImGui::SameLine(0.0f, 10.0f);
                ImGui::Text("%d", MeshInfo->Mesh->id_vertex);

                //ImGui::Separator();
                //ImGui::Text("Mesh Path:");
                //ImGui::SameLine();
                //ImGui::TextColored({ 255,255,0,1 }, "%s", &MeshInfo->File_Path);

                if (ImGui::TreeNodeEx("Vertex Normals:", ImGuiTreeNodeFlags_DefaultOpen)) {

                    ImGui::Checkbox("Show Vertex Normals", &item->showVertexNormals);
                    ImGui::TreePop();
                }

                ImGui::Text("Bounding Boxes:");
                ImGui::Checkbox("Show AABB", &MeshInfo->show_aabb);
                ImGui::Checkbox("Show OBB", &MeshInfo->show_obb);
            }

        }

        if (TextureInfo != nullptr)
        {

            //TEXTURES INFO
            if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen)) {

                ImGui::Checkbox("Checkered", &item->is_Checkered);

                if (item->is_Checkered == true) {
                    TextureInfo->is_Textured = false;
                }

                ImGui::Checkbox("Textured", &TextureInfo->is_Textured);

                if (TextureInfo->is_Textured == true) {
                    item->is_Checkered = false;
                }

                ImGui::Text("Texture Name: ");
                ImGui::SameLine(0.0f, 10.0f);
                const char* nameTexture = TextureInfo->Texture->texture_name.c_str();
                ImGui::TextColored({ 255,255,0,1 }, "%s", nameTexture);

                if (TextureInfo->is_Textured) {
                    ImGui::Text("Texture Path:");
                    ImGui::SameLine(0.0f, 10.0f);
                    const char* pathnameTexture = TextureInfo->Texture->texture_path.c_str();
                    ImGui::TextColored({ 255,255,0,1 }, "%s", pathnameTexture);
                }
                else if (item->is_Checkered) {
                    ImGui::Text("Texture Path:");
                    ImGui::SameLine(0.0f, 10.0f);

                    ImGui::Text("Checkered Texture");
                }
                else {
                    ImGui::Text("Texture Path:");
                    ImGui::SameLine(0.0f, 10.0f);

                    ImGui::Text("No texture Selected");
                }

                ImGui::Text("Texture Width");
                ImGui::SameLine(0.0f, 10.0f);
                ImGui::TextColored({ 255,255,0,1 }, "%d", TextureInfo->Texture->width);

                ImGui::Text("Texture Height");
                ImGui::SameLine(0.0f, 10.0f);
                ImGui::TextColored({ 255,255,0,1 }, "%d", TextureInfo->Texture->height);

                ImGui::Text("Texture id");
                ImGui::SameLine(0.0f, 10.0f);
                ImGui::TextColored({ 255,255,0,1 }, "%d", TextureInfo->Texture->texture_id);

                ImGui::Image((void*)(intptr_t)TextureInfo->Texture->texture_id, { 200,200 });
            }
        }

    

    if (CameraInfo != nullptr)
    {
        Component_Camera* comp_camera = (Component_Camera*)App->camera->GetSceneCamera();

        if (ImGui::CollapsingHeader("Camera Settings", ImGuiTreeNodeFlags_DefaultOpen)) {

            float camSpeed = comp_camera->GetCameraSpeed();
            if (ImGui::DragFloat("Camera Speed", &camSpeed, 0.05f, 0.1f))
            {
                comp_camera->SetCameraSpeed(camSpeed);
            }

            float wheelSpeed = comp_camera->GetWheelSpeed();
            if (ImGui::DragFloat("Wheel Speed Value", &wheelSpeed, 0.05f, 0.1f))
            {
                comp_camera->SetWheelSpeed(wheelSpeed);
            }

            float zoomValue = comp_camera->GetZoomValue();
            if (ImGui::DragFloat("Zoom Value", &zoomValue, 0.05f, 0.1f))
            {
                comp_camera->SetZoomValue(zoomValue);
            }
        }

        if (ImGui::CollapsingHeader("Frustum Settings", ImGuiTreeNodeFlags_DefaultOpen)) {


            float verticalFov = comp_camera->GetFOV();
            if (ImGui::DragFloat("Field of View", &verticalFov, 0.1f, 0.1f))
            {
                comp_camera->SetFOV(verticalFov);
            }

            float nearPlane = comp_camera->GetNearPlane();
            if (ImGui::DragFloat("Near Plane Distance", &nearPlane, 0.5f, 0.1f))
            {
                comp_camera->SetNearPlane(nearPlane);
            }

            float farPlane = comp_camera->GetFarPlane();
            if (ImGui::DragFloat("Far Plane Distance", &farPlane, 0.5f, 0.1f))
            {
                comp_camera->SetFarPlane(farPlane);
            }
            
        }
    }

    if (ListInfo != nullptr)
    {
        if (ImGui::CollapsingHeader("Listener Settings", ImGuiTreeNodeFlags_DefaultOpen)) {

            ImGui::Image((void*)(intptr_t)App->textureImporter->DrawListenerIcon.texture_id, { 25,25 });
            ImGui::SameLine();
            ImGui::Text("Audio Listener");
            
        }
    }

    if (SourceInfo != nullptr)
    {
        if (ImGui::CollapsingHeader("Audio Settings", ImGuiTreeNodeFlags_DefaultOpen)) {

            if (SourceInfo->isPaused != true)
            {
                if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawPlayIcon.texture_id, { 25,25 }) /*&& SourceInfo->isStopped == true*/)
                {
                    //Play button


                    if (SourceInfo->isPlaying != true)
                    {
                        SourceInfo->isPlaying = true;
                        SourceInfo->WiseItem->PlayEvent(SourceInfo->id);
                        SourceInfo->isStopped = false;
                        SourceInfo->isModified = true;
                    }


                }

                ImGui::SameLine();
            }


            if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawResumeIcon.texture_id, { 25,25 }) /*&& SourceInfo->isStopped == false*/)
            {
                //Resume Button
                SourceInfo->WiseItem->ResumeEvent(SourceInfo->id);
                SourceInfo->isModified = true;
            }

            ImGui::SameLine();

            if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawPauseIcon.texture_id, { 25,25 }))
            {
                //Pause Button
                SourceInfo->WiseItem->PauseEvent(SourceInfo->id);

                SourceInfo->isPaused = true;
                SourceInfo->isModified = true;

            }

            ImGui::SameLine();
           
            if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawStopIcon.texture_id, { 25,25 }))
            {
                //Stop Button 

                if (SourceInfo->isPlaying == true)
                {
                    SourceInfo->isPlaying = false;
                    SourceInfo->WiseItem->StopEvent(SourceInfo->id);
                    SourceInfo->isStopped = true;
                    SourceInfo->isPaused = false;
                    SourceInfo->isModified = true;
                }
            }
            
            ImGui::Image((void*)(intptr_t)App->textureImporter->DrawMuteIcon.texture_id, { 20,20 });
            ImGui::SameLine();
            if (ImGui::SliderFloat("Volume", &SourceInfo->WiseItem->StoredVolume, 0, 2))
            {
                SourceInfo->WiseItem->SetVolume(SourceInfo->id, SourceInfo->WiseItem->StoredVolume);

                //SourceInfo->WiseItem->StoredVolume = SourceInfo->WiseItem->volume;
            }
           
            ImGui::SameLine();
            ImGui::Image((void*)(intptr_t)App->textureImporter->DrawFullVoIcon.texture_id, { 20,20 });

            if (SourceInfo->isSpatialDependant == false)
            {
                if (ImGui::SliderInt("Fade Time", &App->scene->time_change_music, 5, 60))
                {

                }
            }

        }
    }

    if (SourceInfo != nullptr)
    {
        if (ImGui::CollapsingHeader("Effects", ImGuiTreeNodeFlags_DefaultOpen)) {

            if (ImGui::Button("Reset Values", {95,20}))
            {
                SourceInfo->WiseItem->reset_vals = true;
            }

            ImGui::SliderFloat("Pitch", (float*)&SourceInfo->WiseItem->val_pitch, -100, 100);
            ImGui::SliderFloat("High-Pass", (float*)&SourceInfo->WiseItem->val_high, -100, 100);
            ImGui::SliderFloat("Low-Pass", (float*)&SourceInfo->WiseItem->val_low, -100, 100);
        }
    }

  
    std::vector<Game_Object*>::iterator It = item->Children_List.begin();

    for (int ChildSpatial = 0; ChildSpatial < item->Children_List.size(); ++ChildSpatial) {

        Game_Object* ItVal = *It;

        Component_Mesh* ComponentMeshesChild = (Component_Mesh*)ItVal->GetComponent(Component_Types::Mesh);

        Component_Transform* ComponentTransformChild = (Component_Transform*)ItVal->GetComponent(Component_Types::Transform);

        Component_Source* ComponentSourceChild = (Component_Source*)ItVal->GetComponent(Component_Types::Source);

        
        if(ItVal->isAudioDistanceObject){

            if (ImGui::CollapsingHeader("Spatial Audio Config", ImGuiTreeNodeFlags_DefaultOpen)) {

                ImGui::Checkbox("Show Obb Spatial", &ComponentMeshesChild->show_obb);

                if (ImGui::DragFloat3("Rad", { &ComponentTransformChild->Scale.x }, 2.0f, 0.0f)) {

                    if (ComponentTransformChild->Scale.x < 0.1)
                    {
                        ComponentTransformChild->Scale.x = 0.1;
                    }
                    if (ComponentTransformChild->Scale.y < 0.1)
                    {
                        ComponentTransformChild->Scale.y = 0.1;
                    }
                    if (ComponentTransformChild->Scale.z < 0.1)
                    {
                        ComponentTransformChild->Scale.z = 0.1;
                    }

                    ComponentTransformChild->UpdateTransformationsObjects(ComponentTransformChild->Translation, ComponentTransformChild->Scale, ComponentTransformChild->Rotation);
                }
            }

        }
            ++It;
        
    }

}





