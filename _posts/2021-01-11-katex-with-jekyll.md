---
layout: post
category: blog
title: How to LaTeX in Jekyll using KaTeX
snippet: An ultra simplified guide without requiring a MathJax to KaTeX conversion
tags: [website, latex]
katex: True
---

The `kramdown` parser, default for many jekyll blogs, generates math code using MathJax, a much slower alternative to [KaTeX](https://katex.org/).
There are many ways people have sought to get around this to transform `math/tex` scripts into $$\KaTeX$$ on the client side: Like [this]( https://github.com/rohanchandra/type-theme/blob/c8138f98f5d3d058d6b1467c72b5ab63b51d2eb5/js/katex_init.js) or [this](https://xuc.me/blog/katex-and-jekyll/#). I found this to be cumbersome.

The easiest way I found was to use the $$\KaTeX$$ auto-render extension, if you use GitHub pages for your website. Alternatively you can render server side if you directly set up `kramdown-math-katex` by following [this very informative blog]( https://gendignoux.com/blog/2020/05/23/katex.html#converting-formulas-to-html-with-kramdown).



- TOC
{:toc .toc}

----------------------

# Step 1: Adding KaTeX
Turn on the KaTeX engine by adding this to your `_config.yaml`:
``` markdown
kramdown:
  math_engine: katex
```

# Step 2: Render $$\KaTeX$$
## Method 1: Using the auto-render extension (works for GitHub pages)


We use the [auto-renderer option](https://katex.org/docs/autorender.html). In your `_includes/head.html`, add:

```html
<head>

  ...

  <!--KaTeX-->
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/katex@0.12.0/dist/katex.min.css" integrity="sha384-AfEj0r4/OFrOo5t7NnNe46zW/tFgW6x/bCJG8FqQCEo3+Aro6EYUG4+cU+KJWu/X" crossorigin="anonymous">
  <script defer src="https://cdn.jsdelivr.net/npm/katex@0.12.0/dist/katex.min.js" integrity="sha384-g7c+Jr9ZivxKLnZTDUhnkOnsh30B4H0rpLUpJ4jAIKs4fnJI+sEnkvrMWph2EDg4" crossorigin="anonymous"></script>
  <script defer src="https://cdn.jsdelivr.net/npm/katex@0.12.0/dist/contrib/auto-render.min.js" integrity="sha384-mll67QQFJfxn0IYznZYonOWZ644AWYC+Pt2cHqMaRhXVrursRwvLnLaebdGIlYNa" crossorigin="anonymous"></script>
  <script>
      document.addEventListener("DOMContentLoaded", function() {
          renderMathInElement(document.body, {
              // ...options...
          });
      });
  </script>

</head>
```

## Method 2: Using `kramdown-math-katex`
### Convert formulas to HTML
Then, on your computer, install the `kramdown-math-katex` package in Ruby:

``` bash
gem install kramdown-math-katex
```

`kramdown-math-katex` requires a few dependencies, install them like so:
``` bash
gem install katex
gem install execjs
```

and one of the following javascript engines, if you dont already have them installed:
``` bash
gem install therubyracer
gem install therubyrhino
gem install duktape
```

### Render HTML into $$\LaTeX$$ fonts
Given that we've converted everything into HTML, we now need to render the fonts in the browser using some CSS and various fonts. To do that, we can follow the [$$\KaTeX$$ starter template](https://katex.org/docs/browser.html#starter-template).

As noted by [Guillaume](https://gendignoux.com/blog/2020/05/23/katex.html#which-resources-to-add) we do not need to add the javascripts since we've already obtained the HTML. Therefore, in your `_includes/head.html`, you just need to add:
```html
<head>

  ...

  <!-- KaTeX -->
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/katex@0.12.0/dist/katex.min.css" integrity="sha384-AfEj0r4/OFrOo5t7NnNe46zW/tFgW6x/bCJG8FqQCEo3+Aro6EYUG4+cU+KJWu/X" crossorigin="anonymous">

</head>
```

He also suggests downloading the relevant CSS files and font files only for rendering without an internet connection. Therefore, you can also download the [latest version of $$\KaTeX$$](https://github.com/KaTeX/KaTeX/releases) and then only keeping the `katex.min.css` file and the `fonts/` folder. That way, your snippet will be like:

```html
<head>

  ...

  <!-- KaTeX -->
  <link rel="stylesheet" href="/assets/plugins/katex.0.11.1/katex.min.css">

</head>
```

# Step 3: Toggle on and off (optional)
Lastly, we can make this even more lightweight by adding a toggle on and off option to make other pages more lightweight. To do so, we modify the above script by adding a page property called `katex` and surround the relevant lines with a conditional:

``` html
<head>

  ...
  {% raw  %}
  {% if page.katex %}
  <!-- KaTeX -->
  <link rel="stylesheet" href="/assets/plugins/katex.0.11.1/katex.min.css">
  {% endif %}
  {% endraw %}

</head>
```

# Step 4: To use
To every blog page that you intend to use katex, add `katex: True` to your preamble, like so:

```markdown
---
layout: post
title: KaTeX with Jekyll
katex: True
---
inline: $$f(x) = \int_{-\infty}^\infty \hat f(\xi)\,e^{2 \pi i \xi x} \,d\xi$$
display mode (centered):

$$f(x) = \int_{-\infty}^\infty \hat f(\xi)\,e^{2 \pi i \xi x} \,d\xi$$

```

And this gives:


> inline: $$f(x) = \int_{-\infty}^\infty \hat f(\xi)\,e^{2 \pi i \xi x} \,d\xi$$
>
> display mode (centered):
>
> $$f(x) = \int_{-\infty}^\infty \hat f(\xi)\,e^{2 \pi i \xi x} \,d\xi$$
>

Now if you toggle the `katex` property, you can see that the HTML symbols are created, but they will not load in $$\LaTeX$$ font.

# Fast $$\LaTeX$$ to $$\KaTeX$$ commands
There's a [quick list]( `https://katex.org/docs/supported.html`) and a [complete list](https://katex.org/docs/support_table.html) of supported functions.

Some of the canonical ones:
- Inline: `$x$` to `$$x$$` with no line spacing before or after (see above).
- Standalone: `$$f=ma$$` to `$$f=ma$$` with line spacing before and after (see above).
- Equation labeling: `\label{eq:test}` to `\tag{1}` (manually labeled equations)
- Haven't figured out how to do bibtex

# Notes

I first transcribe a $$\LaTeX$$ document into github-flavored markdown (GFM) using [pandoc](https://pandoc.org/):
```bash
pandoc -f latex -t markdown file.tex
```
This is really nice because it actually converts all of my custom macros into just plain latex, which is good enough most of the time.
However, the above modifications (inline, standalone, any labeling) will need to be made after the transcription in order for it to work with $$\KaTeX$$.

Things to edit after transcribing:
- Pandoc doesn't transcribe two of `^` in sequence well, but you can fix that manually.
- Pandoc adds an extra `\` at the end of a paragraph. This needs to be removed.
- Can remove the `\nonumber` attribute in equations.
- Equation referencing isn't available, therefore add appropriate `\tag{}` attributes and label them manually.
