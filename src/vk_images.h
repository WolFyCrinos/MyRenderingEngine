//
// Created by FrançoisMARTEEL on 6/1/2024.
//

#ifndef MYRENDERINGENGINE_VK_IMAGES_H
#define MYRENDERINGENGINE_VK_IMAGES_H

#endif //MYRENDERINGENGINE_VK_IMAGES_H

#pragma once

#include <vulkan/vulkan.h>

namespace vkutil {

    void transition_image(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout);

    void copy_image_to_image(VkCommandBuffer cmd, VkImage source, VkImage destination,VkExtent2D srcSize, VkExtent2D dstSize);

    void generate_mipmaps(VkCommandBuffer cmd, VkImage image, VkExtent2D imageSize);
}