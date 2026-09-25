import fs from 'node:fs';
import path from 'node:path';
import { pathToFileURL } from 'node:url';
import { createRequire } from 'node:module';
import { marked } from 'file:///C:/Users/Administrator/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/marked/lib/marked.esm.js';

const require = createRequire(import.meta.url);
const katex = require('./node_modules/katex');
const { chromium } = require('C:/Users/Administrator/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/playwright');
const root = path.dirname(new URL(import.meta.url).pathname.replace(/^\/(?=[A-Za-z]:)/,''));
const built = path.join(root,'built');
const stage = path.join(root,'pdf_stage');
fs.mkdirSync(stage,{recursive:true});

function mathReplace(source){
  const html=[];
  source = source.replace(/\$\$([\s\S]+?)\$\$/g,(_all,formula)=>{
    const value = katex.renderToString(formula,{displayMode:true,throwOnError:true,strict:'ignore'});
    html.push(`<div class="formula">${value}</div>`);
    return `MATHBLOCKPLACEHOLDER${html.length - 1}END`;
  });
  source = source.replace(/\$([^\$\n]+?)\$/g,(_all,formula)=>{
    const value = katex.renderToString(formula,{displayMode:false,throwOnError:true,strict:'ignore'});
    html.push(value);
    return `MATHINLINEPLACEHOLDER${html.length - 1}END`;
  });
  let out=marked.parse(source);
  out=out.replace(/<p>MATHBLOCKPLACEHOLDER(\d+)END<\/p>/g,(_all,index)=>html[Number(index)]);
  out=out.replace(/MATHINLINEPLACEHOLDER(\d+)END/g,(_all,index)=>html[Number(index)]);
  out=out.replace(/<pre><code class="language-mermaid">([\s\S]*?)<\/code><\/pre>/g,(_all,code)=>{
    const clean=code.replaceAll('&gt;','>').replaceAll('&lt;','<').replaceAll('&amp;','&').replaceAll('&quot;','"');
    return `<div class="mermaid">${clean}</div>`;
  });
  out=out.replace(/(<h3>[^<]*(?:搜索|状态图)[^<]*<\/h3>\s*<p>[\s\S]*?<\/p>\s*<p><strong>左上角图例<\/strong>[\s\S]*?<\/p>\s*<div class="mermaid">[\s\S]*?<\/div>\s*<p><strong>叶子<\/strong>[\s\S]*?<\/p>)/g,'<div class="diagram-block">$1</div>');
  return out;
}

function documentHtml(parts,kind){
  const body=parts.map((p,i)=>`<section class="problem ${i ? 'new-page' : ''} ${p.startsWith('# 绿野仙踪') ? 'compact-green' : ''}">${mathReplace(p)}</section>`).join('\n');
  return `<!doctype html><html lang="zh-CN"><head><meta charset="utf-8">
<link rel="stylesheet" href="../node_modules/katex/dist/katex.min.css">
<style>
@page { size: A4; margin: 10mm 15mm 10mm 15mm; }
* { box-sizing: border-box; }
html,body { margin:0; padding:0; }
body { font-family: "Microsoft YaHei", "Noto Sans CJK SC", Arial, sans-serif; color:#17212e; font-size:10pt; line-height:1.55; }
body.solution { font-size:9.3pt; line-height:1.42; }
body.solution h2 { margin-top:11pt; }
body.solution h3 { margin-top:8pt; }
body.solution p { margin:4pt 0 5pt; }
body.solution ol { margin:3pt 0 5pt; }
body.solution li { margin:1pt 0; }
body.solution pre { font-size:7.1pt; line-height:1.11; padding:5pt; margin:4pt 0 6pt; }
body.statement,body.summary { font-size:8.8pt; line-height:1.34; }
body.statement h1,body.summary h1 { font-size:16.5pt; }
body.statement h2,body.summary h2 { font-size:11pt; margin-top:8pt; }
body.statement h3,body.summary h3 { font-size:9.5pt; margin-top:7pt; }
body.statement p,body.summary p { margin:3pt 0 4.5pt; }
body.statement ul,body.summary ul { margin:3pt 0 5pt; }
body.statement li,body.summary li { margin:1pt 0; }
body.statement pre,body.summary pre { font-size:7.4pt; padding:5pt; line-height:1.18; margin:4pt 0 6pt; }
body.statement table,body.summary table { font-size:8pt; margin:5pt 0 6pt; }
body.statement th,body.statement td,body.summary th,body.summary td { padding:2.5pt 4pt; }
body.statement .compact-green,body.summary .compact-green { font-size:8.3pt; line-height:1.23; }
body.statement .compact-green h2,body.summary .compact-green h2 { margin-top:6pt; }
body.statement .compact-green p,body.summary .compact-green p { margin:2pt 0 3pt; }
body.statement .compact-green pre,body.summary .compact-green pre { font-size:7.1pt; line-height:1.1; padding:3pt; margin:3pt 0 4pt; }
body.statement .compact-green table,body.summary .compact-green table { font-size:7.6pt; margin:3pt 0 4pt; }
body.statement .compact-green th,body.statement .compact-green td,body.summary .compact-green th,body.summary .compact-green td { padding:1.8pt 3pt; }
section.new-page { break-before: page; }
.heading-block { break-inside:avoid; }
h1,h2,h3 { color:#0d2942; break-after:avoid; margin-bottom:0; }
h1 { font-size:19pt; margin-top:0; line-height:1.35; }
h2 { font-size:13pt; margin-top:17pt; }
h3 { font-size:10.5pt; margin-top:13pt; }
h1 + hr,h2 + hr { border:0; border-top:0.7pt solid #9ba8b6; margin:5pt 0 10pt; }
p { margin:6pt 0 8pt; orphans:2; widows:2; }
ul,ol { margin:5pt 0 8pt; padding-left:18pt; }
li { margin:2pt 0; }
pre { font-family: Consolas,"Courier New",monospace; font-size:7.5pt; line-height:1.23; background:#f6f8fa; border:0.6pt solid #d8e0e8; border-radius:3pt; padding:7pt; white-space:pre-wrap; overflow-wrap:anywhere; tab-size:4; margin:7pt 0 11pt; }
code { font-family: Consolas,"Courier New",monospace; font-size:0.92em; }
pre code { font-size:inherit; }
table { border-collapse:collapse; width:100%; font-size:9pt; margin:8pt 0 11pt; }
th,td { border:0.55pt solid #b9c5d0; padding:4pt 5pt; vertical-align:top; }
th { background:#edf2f6; }
.formula { text-align:center; margin:10pt 0; overflow:hidden; }
.katex-display { margin:0; }
.diagram-block { break-inside:avoid; }
.mermaid { text-align:center; break-inside:avoid; margin:5pt auto 6pt; }
.mermaid svg { max-width:100% !important; max-height:65mm !important; }
strong { color:#102b43; }
</style></head><body class="${kind}">${body}
<script src="../node_modules/mermaid/dist/mermaid.min.js"></script></body></html>`;
}

async function render(browser,parts,target,kind){
  const htmlPath=path.join(stage,path.basename(target)+'.html');
  fs.writeFileSync(htmlPath,documentHtml(parts,kind),'utf8');
  const page=await browser.newPage({viewport:{width:1050,height:1485},deviceScaleFactor:1});
  await page.goto(pathToFileURL(htmlPath).href,{waitUntil:'load'});
  await page.evaluate(async()=>{
    await document.fonts.ready;
    if(document.querySelector('.mermaid')){
      mermaid.initialize({startOnLoad:false,theme:'neutral',securityLevel:'loose',themeVariables:{fontSize:'13px'},flowchart:{htmlLabels:true,curve:'linear',nodeSpacing:16,rankSpacing:18,padding:5}});
      await mermaid.run({querySelector:'.mermaid'});
    }
    for(const heading of document.querySelectorAll('h1,h2')){
      const rule=heading.nextElementSibling;
      const first=rule?.nextElementSibling;
      if(rule?.tagName==='HR' && first){
        const keep=document.createElement('div');
        keep.className='heading-block';
        heading.parentElement.insertBefore(keep,heading);
        keep.append(heading,rule,first);
      }
    }
  });
  const errors=await page.locator('.mermaid .error').count();
  if(errors) throw new Error(`Mermaid errors: ${errors} in ${target}`);
  await page.pdf({path:target,format:'A4',preferCSSPageSize:true,printBackground:true,displayHeaderFooter:true,
    headerTemplate:'<div></div>',footerTemplate:'<div style="width:100%;font-size:8px;color:#768391;text-align:center"><span class="pageNumber"></span></div>'});
  await page.close();
}

const browser=await chromium.launch({headless:true,executablePath:'C:/Program Files/Google/Chrome/Application/chrome.exe'});
try {
  const sourceArg = process.argv.find(arg=>/^--source-statement=[4-7]\/[1-4]$/.test(arg));
  if(sourceArg){
    const [suite,task] = sourceArg.split('=')[1].split('/').map(Number);
    const sourceDir=path.join(root,`source${suite}`,`T${task}`,'release');
    const markdown=fs.readFileSync(path.join(sourceDir,'statement.md'),'utf8');
    await render(browser,[markdown],path.join(sourceDir,'statement.pdf'),'statement');
    console.log(`PDF source statement ${suite}/${task}`);
  } else {
  const suiteArg = process.argv.find(arg=>/^\d+$/.test(arg));
  const suites = suiteArg ? [Number(suiteArg)] : [4,5,6,7];
  const solutionOnly = process.argv.includes('--solution-only');
  const statementTaskArg = process.argv.find(arg=>/^--statement-task=[1-4]$/.test(arg));
  const statementTask = statementTaskArg ? Number(statementTaskArg.slice(-1)) : null;
  for(const suite of suites){
    const dir=path.join(built,`suite${suite}_full`);
    const statements=[];
    for(let task=1;task<=4;task++){
      const p=path.join(dir,`T${task}`);
      const md=fs.readFileSync(path.join(p,'statement.md'),'utf8');
      statements.push(md);
      if(!solutionOnly && (statementTask === null || task === statementTask)){
        await render(browser,[md],path.join(p,'statement.pdf'),'statement');
        console.log(`PDF statement ${suite}/${task}`);
      }
    }
    const solutions=[];
    for(let task=1;task<=4;task++) solutions.push(fs.readFileSync(path.join(dir,`T${task}`,'solution.md'),'utf8'));
    await render(browser,solutions,path.join(dir,'solution.pdf'),'solution');
    if(!solutionOnly) await render(browser,statements,path.join(dir,'题目汇总.pdf'),'summary');
    console.log(`PDF suite ${suite}`);
  }
  }
} finally { await browser.close(); }
