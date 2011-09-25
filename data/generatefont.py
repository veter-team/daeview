import bpy

if len(bpy.context.selected_objects) > 0 :
    selected_obj = bpy.context.selected_objects[0]
    material_name = selected_obj.material_slots[0].name
    font_name = selected_obj.data.name
    font_size = selected_obj.data.size
    selected_obj.select = False

    s = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~"

    for c in s:
        extrude = selected_obj.data.extrude

        bpy.ops.object.text_add()
        new_obj = bpy.data.scenes[0].objects[0]

        new_obj.name = font_name + "." + str(ord(c))
        new_obj.data.body = c
        new_obj.data.size = font_size
        new_obj.data.extrude = extrude
        new_obj.data.materials.append(bpy.data.materials[material_name])

        new_obj.location.x = 0
        new_obj.location.y = 0
        new_obj.location.z = 0
        
        # Convert to mesh
        new_obj.select = True
        bpy.ops.object.convert()
