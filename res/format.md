Use with the web tool https://kitzsh.github.io/tex-packer-ex/:

```
const AtlasSprite atlas_sprites[] = {
{{#rects}}
    { {{frame.x}}, {{frame.y}}, {{frame.w}}, {{frame.h}}, {{sourceSize.w}}, {{sourceSize.h}} }, // {{{name}}}
{{/rects}}
};
```