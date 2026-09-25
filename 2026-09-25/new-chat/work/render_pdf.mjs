import fs from 'node:fs';
import path from 'node:path';
import { pathToFileURL } from 'node:url';
import { createRequire } from 'node:module';
import { marked } from 'file:///C:/Users/Administrator/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/marked/lib/marked.esm.js';

const require = createRequire(import.meta.url);
const modules = 'C:/Users/Administrator/Desktop/OI-/2026-09-24/new-chat/work/node_modules';
const katex = require(modules + '/katex');
const { chromium } = require('C:/Users/Administrator/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/playwright');
const root = path.dirname(new URL(import.meta.url).pathname.replace(/^\/(?=[A-Za-z]:)/, ''));
const built = path.join(root, 'built');
const stage = path.join(root, 'pdf_stage');
fs.mkdirSync(stage, {recursive:true});

function mathReplace(source){
  const pieces = [];
  source = source.replace(/\$\$([\s\S]+?)\$\$/g, (_m, x) => {
    const y = katex.renderToString(x, {displayMode:true, throwOnError:true, strict:'ignore'});
    pieces.push(`<div class="formula">${y}</div>`);
    return `MATHBLOCKPLACEHOLDER${pieces.length - 1}END`;
  });
  source = source.replace(/\$([^\$\n]+?)\$/g, (_m, x) => {
    pieces.push(katex.renderToString(x, {displayMode:false, throwOnError:true, strict:'ignore'}));
    return `MATHINLINEPLACEHOLDER${pieces.length - 1}END`;
  });
  let out = marked.parse(source);
  out = out.replace(/<p>MATHBLOCKPLACEHOLDER(\d+)END<\/p>/g, (_m, n) => pieces[Number(n)]);
  out = out.replace(/MATHINLINEPLACEHOLDER(\d+)END/g, (_m, n) => pieces[Number(n)]);
  out = out.replace(/<pre><code class="language-mermaid">([\s\S]*?)<\/code><\/pre>/g, (_m, code) => {
    return `<div class="mermaid">${code.replaceAll('&gt;', '>').replaceAll('&lt;', '<').replaceAll('&amp;', '&').replaceAll('&quot;', '"')}</div>`;
  });
  return out;
}

const cssPath = pathToFileURL(modules + '/katex/dist/katex.min.css').href;
const mermaidPath = pathToFileURL(modules + '/mermaid/dist/mermaid.min.js').href;
function html(parts, kind){
  const body = parts.map((text, i) => `<section class="problem ${i ? 'new-page' : ''}">${mathReplace(text)}</section>`).join('\n');
  return `<!doctype html><html lang="zh-CN"><head><meta charset="utf-8"><link rel="stylesheet" href="${cssPath}"><style>
@page{size:A4;margin:10mm 15mm 10mm 15mm}
*{box-sizing:border-box}
body{font-family:"Microsoft YaHei","Noto Sans CJK SC",Arial,sans-serif;color:#1b2733;font-size:9.3pt;line-height:1.43}
body.statement,body.summary{font-size:9.8pt;line-height:1.43}
section.new-page{break-before:page}
.heading-block{break-inside:avoid}
h1,h2,h3{color:#16324d;break-after:avoid;margin-bottom:0}
h1{font-size:19pt;margin-top:0}h2{font-size:13pt;margin-top:12pt}h3{font-size:10.5pt;margin-top:9pt}
h1+hr,h2+hr{border:0;border-top:.7pt solid #9ba8b6;margin:5pt 0 9pt}
p{margin:4pt 0 6pt;orphans:2;widows:2}ol,ul{margin:4pt 0 6pt;padding-left:18pt}li{margin:2pt 0}
pre{font-family:Consolas,"Courier New",monospace;font-size:7.0pt;line-height:1.12;background:#f6f8fa;border:.6pt solid #d8e0e8;border-radius:3pt;padding:5pt;white-space:pre-wrap;overflow-wrap:anywhere;tab-size:4;margin:5pt 0 7pt}
body.statement pre,body.summary pre{font-size:8.2pt}
code{font-family:Consolas,"Courier New",monospace;font-size:.92em}pre code{font-size:inherit}
table{border-collapse:collapse;width:100%;font-size:9pt;margin:7pt 0 9pt}th,td{border:.55pt solid #b9c5d0;padding:4pt 5pt;vertical-align:top}th{background:#edf2f6}
.formula{text-align:center;margin:8pt 0;overflow:hidden}.katex-display{margin:0}
.mermaid{text-align:left;break-inside:avoid;margin:5pt 0 6pt}.mermaid svg{max-width:100%!important;max-height:75mm!important}
strong{color:#15344e}
</style></head><body class="${kind}">${body}<script src="${mermaidPath}"></script></body></html>`;
}

async function render(browser, parts, target, kind){
  const htmlPath = path.join(stage, path.basename(target) + '.' + kind + '.html');
  fs.writeFileSync(htmlPath, html(parts, kind), 'utf8');
  const page = await browser.newPage({viewport:{width:1050,height:1485},deviceScaleFactor:1});
  await page.goto(pathToFileURL(htmlPath).href, {waitUntil:'load'});
  await page.evaluate(async () => {
    await document.fonts.ready;
    if(document.querySelector('.mermaid')){
      mermaid.initialize({startOnLoad:false,theme:'neutral',securityLevel:'loose',themeVariables:{fontSize:'13px'},flowchart:{htmlLabels:true,curve:'linear',nodeSpacing:22,rankSpacing:20,padding:8}});
      await mermaid.run({querySelector:'.mermaid'});
    }
    for(const h of document.querySelectorAll('h1,h2')){
      const hr = h.nextElementSibling;
      const first = hr?.nextElementSibling;
      if(hr?.tagName === 'HR' && first){
        const keep = document.createElement('div');
        keep.className = 'heading-block';
        h.parentElement.insertBefore(keep, h);
        keep.append(h,hr,first);
      }
    }
  });
  const errors = await page.locator('.mermaid .error').count();
  if(errors) throw new Error(`Mermaid error ${errors}: ${target}`);
  await page.pdf({path:target,format:'A4',preferCSSPageSize:true,printBackground:true,displayHeaderFooter:true,
    headerTemplate:'<div></div>',footerTemplate:'<div style="width:100%;font-size:8px;color:#778599;text-align:center"><span class="pageNumber"></span></div>'});
  await page.close();
  console.log(target);
}

const browser = await chromium.launch({headless:true,executablePath:'C:/Program Files/Google/Chrome/Application/chrome.exe'});
try{
  const statements = [];
  const solutions = [];
  for(let i=1;i<=4;i++){
    const dir = path.join(built, `T${i}`);
    const statement = fs.readFileSync(path.join(dir,'statement.md'),'utf8');
    const solution = fs.readFileSync(path.join(dir,'solution.md'),'utf8');
    statements.push(statement);
    solutions.push(solution);
    await render(browser,[statement],path.join(dir,'statement.pdf'),'statement');
  }
  await render(browser,statements,path.join(built,'题目汇总.pdf'),'summary');
  await render(browser,solutions,path.join(built,'solution.pdf'),'solution');
}finally{
  await browser.close();
}
