---
layout: post
category: blog
title: What is SORA AI Model from OpenAI
snippet: Sora is an AI model developed by OpenAI that can create realistic and imaginative scenes from text instructions
tags: [AI]
katex: True
---
## I. What is SORA AI Model 
Sora is an AI model developed by OpenAI that can create realistic and imaginative scenes from text instructions. It is a text-to-video model capable of generating videos up to a minute long while maintaining visual quality and adherence to the user's prompt. The model can create complex scenes with multiple characters, specific types of motion, and accurate details of the subject and background. Sora serves as a foundation for models that can understand and simulate the real world, with the goal of training models that help people solve problems requiring real-world interaction. As of now, Sora is not widely available, and there is no public access or API access. OpenAI is working with red teamers and building tools to ensure the safety of the model before making it available in their products

[https://openai.com/sora](https://openai.com/sora)

## 2. Summary technical report of SORA
You can find the detail in here: 
[Video generation models as world simulators](https://openai.com/research/video-generation-models-as-world-simulators)
<div class="tip">
"We explore large-scale training of generative models on video data. Specifically, we train text-conditional diffusion models jointly on videos and images of variable durations, resolutions and aspect ratios. We leverage a transformer architecture that operates on spacetime patches of video and image latent codes. Our largest model, Sora, is capable of generating a minute of high fidelity video. Our results suggest that scaling video generation models is a promising path towards building general purpose simulators of the physical world."
</div>
The core idea behind Vision Transformers, and data processing for Sora, seems to be based on embedding chunks of video down into a latent space called a patch, which then acts like a token.

{% include image.html url="/assets/2024-02-15-SORA/figure-patches.png" description="SORA " width="60%" %}

Sora is trained to predict the original "clean" patches from noisy patches, given input and conditioning information like text prompts by using diffusion model.
 
{% include image.html url="/assets/2024-02-15-SORA/figure-diffusion.png" description="SORA " width="60%" %}

Sora's capabilities include generating videos up to a minute long while maintaining visual quality and adherence to the user's prompt. The model has a deep understanding of language, enabling it to accurately interpret prompts and generate compelling characters that express vibrant emotions. However, it may struggle with accurately simulating the physics of a complex scene and understanding specific instances of cause and effect.

## Demo SORA from OpenAI 

{% include youtube.html id="HK6y8DAPN_0" %}

## References:
1. [https://openai.com/sora](https://openai.com/sora)
2. [https://openai.com/research/video-generation-models-as-world-simulators](https://openai.com/research/video-generation-models-as-world-simulators)