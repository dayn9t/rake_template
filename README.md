# 海康排他网络(Hik Exclusive Network)

## Rake 

Rake 参见: https://github.com/dayn9t/rake.
这是 Rake 项目的一个模板.
```
sed -i 's/rat/<NS>/g' `rg -l rat`
sed -i 's/net/<MOD_A>/g' `rg -l net`
net
sed -i 's/hennet/<MOD_A>/g' `rg -l hennet`

```

## 音频转码

最具性价比的是 mp3 格式, aac 必须 32bit 32k, 大很多
- G.711 A-law 转 wav: ```ffmpeg -f s16le -acodec pcm_alaw -ar 8000 -ac 1 -i input.raw output.wav```
    - ***注意input要放在格式之后***
- G.711 A-law 转 wav: ```ffmpeg -f s16le -acodec pcm_alaw -ar 8000 -ac 1 -i input.raw -ar 16000 output.mp3```
    - 需要加是16K采样率,否则有杂音


## 部署

- 海康库可以系统库
- 