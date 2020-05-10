# Updating Old ReasonML Code with [bloodyowl/upgrade-reason-react-esy](https://github.com/bloodyowl/upgrade-reason-react-esy)

# What Is This?

I have this riduculous process for figuring things out with [`reasonml`](https://reasonml.org). Basically it entails trying to do something, hitting a wall. Hitting the docs for whatever code I am trying to use, then rummaging around `Github` for some code that implements what I am trying to do.

A lot of the time, that code is in old `reasonml` syntax or in `ocaml`. I end up learning the `ocaml`, converting it to `reasonml` or often times, updating old projects until they work again.

Today, for example, I discovered [`Iwan Karamazow's`](https://github.com/IwanKaramazow) git repos. Had to know what his 4 year old [transducers.re](https://github.com/IwanKaramazow/transducers.re) was about. So I forked and updated it until it [compiled](https://github.com/idkjs/transducers.re). I still can't figure out how to call the functions and asked him about it. We will see if he is still interested in it. That led me to some more old code demonstrating `transducers` in [@oddlyfunctional](https://twitter.com/oddlyfunctional)'s [oddlyfunctional/bs-transducers](https://github.com/oddlyfunctional/bs-transducers), which then sent me to to his 2 year old[form-builder-reasonml](https://github.com/oddlyfunctional/form-builder-reasonml) repo which is the subject of this code study today.

Thank you to Iwan and Mario for sharing their transducers!


# Here We Go!

This code is super old so we are going to have to lean on [bloodyowl/upgrade-reason-react-esy](https://github.com/bloodyowl/upgrade-reason-react-esy).

Let `clone`, `fork`, `download` the target repo to get started.

```sh
git clone https://github.com/oddlyfunctional/form-builder-reasonml old-code-update
```

Let's follow the not to heavy [upgrade-reason-react-esy README](https://github.com/bloodyowl/upgrade-reason-react-esy#README.md) instructions.

1. `npm i bloodyowl-upgrade-reason-react`.

Trying to install fails. I am guessing its because of some `package-lock.json` dependency.

Lets `rm package-lock.json` to get rid of the old dependencies interfering. I am also going to get rid of the `node`,`grpc@1.13.1`, `node-pre-grp` and `bs-platform@4.0.7` files since, first, why are they there?, and second,not the point of what we are doing here.

Lets run:

```sh
rm package-lock.json node grpc@1.13.1 node-pre-grp bs-platform@4.0.7
``` 

Try installing again, `npm install`. This takes a while because it has to build `grpc@1.13.1`. Installing fails again because the project requires `node 10.x` listed in `engines` in `package.json`. I am using [`fnm`](https://github.com/Schniz/fnm) so I will add the expected version with `fnm install 10` the set it on this directory with `fnm use 10`. 

Run `npm install` again and it works.

Try installing the upgrade package again and it works:

```sh
> npm i bloodyowl-upgrade-reason-react
```

Next we will run `find src -name "*.re" | yarn Upgrade` as per the docs.

Here is the output if you run the command, but don't just yet:

```sh
~/Github/old-code-update updating* 21s
❯ find src -name "*.re" | yarn Upgrade
yarn run v1.22.4
$ /Users/mandalarian/Github/old-code-update/node_modules/.bin/Upgrade
 UpgradeRR  Done  src/AlternateChoices.re
 UpgradeRR  Done  src/Answer.re
 UpgradeRR  Done  src/AnswerDB.re
 UpgradeRR  Done  src/App.re
 UpgradeRR  Done  src/AppContext.re
 UpgradeRR  Done  src/Authenticated.re
 UpgradeRR  Done  src/Context.re
 UpgradeRR  Done  src/EditQuestionnaire/EditQuestionnaire.re
 UpgradeRR  Done  src/EditQuestionnaire/QuestionField.re
 UpgradeRR  Done  src/EditQuestionnaire/SelectQuestionType.re
 UpgradeRR  Done  src/EditQuestionnaire/TextInput.re
 UpgradeRR  Done  src/Firebase.re
 UpgradeRR  Done  src/FirebaseAuth.re
 UpgradeRR  Done  src/Form.re
 UpgradeRR  Done  src/Index.re
 UpgradeRR  Done  src/Link.re
 UpgradeRR  Done  src/ListQuestionnaires.re
 UpgradeRR  Done  src/MultipleChoices.re
 UpgradeRR  Done  src/QuestionnaireDB.re
 UpgradeRR  Done  src/Router.re
 UpgradeRR  Done  src/SharedTypes.re
 UpgradeRR  Done  src/ShowQuestionnaire.re
 UpgradeRR  Done  src/ShowQuestionnaireAnswers.re
 UpgradeRR  Done  src/Styles.re
 UpgradeRR  Done  src/TextArea.re
 UpgradeRR  Done  src/TextField.re
 UpgradeRR  Done  src/Utils.re
Done!
✨  Done in 0.72s.

~/Github/old-code-update updating*
❯ 
```

Instead of outputing the result to the terminal, let's run it and push the output to a file:

```sh
❯ find src -name "*.re" | yarn Upgrade > edits.cfg
```

It should look something like:

```txt
yarn run v1.22.4
$ /Github/old-code-update/node_modules/.bin/Upgrade
 UpgradeRR  Done  src/AlternateChoices.re
 UpgradeRR  Done  src/Answer.re
 UpgradeRR  Done  src/AnswerDB.re
 UpgradeRR  Done  src/App.re
 UpgradeRR  Done  src/AppContext.re
 UpgradeRR  Done  src/Authenticated.re
 UpgradeRR  Done  src/Context.re
 UpgradeRR  Done  src/EditQuestionnaire/EditQuestionnaire.re
 UpgradeRR  Done  src/EditQuestionnaire/QuestionField.re
 UpgradeRR  Done  src/EditQuestionnaire/SelectQuestionType.re
 UpgradeRR  Done  src/EditQuestionnaire/TextInput.re
 UpgradeRR  Done  src/Firebase.re
 UpgradeRR  Done  src/FirebaseAuth.re
 UpgradeRR  Done  src/Form.re
 UpgradeRR  Done  src/Index.re
 UpgradeRR  Done  src/Link.re
 UpgradeRR  Done  src/ListQuestionnaires.re
 UpgradeRR  Done  src/MultipleChoices.re
 UpgradeRR  Done  src/QuestionnaireDB.re
 UpgradeRR  Done  src/Router.re
 UpgradeRR  Done  src/SharedTypes.re
 UpgradeRR  Done  src/ShowQuestionnaire.re
 UpgradeRR  Done  src/ShowQuestionnaireAnswers.re
 UpgradeRR  Done  src/Styles.re
 UpgradeRR  Done  src/TextArea.re
 UpgradeRR  Done  src/TextField.re
 UpgradeRR  Done  src/Utils.re
Done!
Done in 0.34s.
```
Doing this will let us be a little more effecient with some terminal scripts later.

# Updating Strings

`@bloodyowl` again:

> If you've alias ReasonReact to React, search and replace it back to ReasonReact. 

> # Search and replace: 

> ReasonReact.Update to Update 

> ReasonReact.UpdateWithSideEffects to UpdateWithSideEffects 

> ReasonReact.SideEffects to SideEffects 

> ReasonReact.NoUpdate to NoUpdate

This seems a bit error prone to redo these steps every time I am up in some random old repo so I wrote this little hack using this awesome random library I came across in my random `reason` project meandering. Its called [FastReplaceString](https://github.com/IwanKaramazow/FastReplaceString) by some hacker named [Iwan Karamazow](https://github.com/IwanKaramazow) who seems to have been active in the early `reason` days. Thanks again, Iwan!

Let's install his utiility:

```sh
npm i -D IwanKaramazow/FastReplaceString
```

Lets create a script called `reasonreactupdate.sh` and put this in it:

```sh
#!/bin/zsh
# get our filelist
file=edits.cfg

# define a function with the changes we want to make and call `fastreplacestring.exe` on each version of tuple
function edits(){
  for i in "ReasonReact.Update Update" "ReasonReact.NoUpdate NoUpdate" "ReasonReact.UpdateWithSideEffects UpdateWithSideEffects"
do
    set -- $i
    echo fastreplacestring.exe $1 $2
done
};

while IFS= read -r cmd; do
    edits $cmd
done < "$file"
```

So what are we doing? Instead of searching for each set of string in our editor we will iterate over tuples of the edits we want to make calling each variation of what [bloodyowl](https://www.twitter.com/@bloodyowl) wants us to do with `fastreplacestring`. For example, the first tuple is 

```re
("ReasonReact.Update Update")
```

So the script will go through and change all the instances of the left side, to the right side of the tuple. Or the first argument to the second argument.

Just for for fun, if you are in a situation where you have aliased the `ReasonReact` as `React` we can just run both changes on all the affected files. I put each variation in a different script to keep my mind from going crazy. 

```sh
# reactupdate.sh handles getting rid of the aliases
file=edits.cfg
function edits(){
  for i in "React.Update ReasonReact.Update" "React.NoUpdate ReasonReact.NoUpdate" "React.UpdateWithSideEffects ReasonReact.UpdateWithSideEffects"
do
    set -- $i
    echo fastreplacestring.exe $1 $2
done
};

while IFS= read -r cmd; do
    edits $cmd
done < "$file"
```

Then in `./replacestrings.sh` we will do:

```sh
#!/bin/zsh

./reactupdate.sh; 
./reasonreactupdate.sh
```

So whether you had used an alias or not, everything gets handled.

Running it looks like this:

```sh
~/Github/old-code-update updating*
❯ ./replacestrings.sh
# running reactupdate.sh ...for every file
fastreplacestring.exe React.Update ReasonReact.Update
fastreplacestring.exe React.NoUpdate ReasonReact.NoUpdate
fastreplacestring.exe React.UpdateWithSideEffects ReasonReact.UpdateWithSideEffects

# ...running reasonreactupdate.sh for every file
fastreplacestring.exe React.Update ReasonReact.Update
fastreplacestring.exe React.NoUpdate ReasonReact.NoUpdate
fastreplacestring.exe React.UpdateWithSideEffects ReasonReact.UpdateWithSideEffects

# ...abbreviated to save your eyes
~/Github/old-code-update updating*
❯ 
```

## Updating ReasonReact

> Install reason-react from [this](https://github.com/bloodyowl/reason-react) fork's master branch.

Now we need to install a specific version of `reason-react` as indicated by the docs along with two more `@bloodyowl` libs,`reason-react-update` and `reason-react-compat`. These will allow us to keep using the old `ReasonReact` api the project.

Needless to say, `@bloodyowl` is a boss.

Run:

```sh
npm i https://github.com/bloodyowl/reason-react 
npm i reason-react-update reason-react-compat
```

# Change JSX version in bsconfig.json
```json
 "reason": {
-  "react-jsx": 2
+  "react-jsx": 3
 },
 ```

 Now you can start the project with `npm start`. What I saw was the following error:

 ```sh
❯ yarn start
yarn run v1.22.4
$ bsb -make-world -w
File "bsconfig.json", line 5:
Error: JSX version 3 is deprecated, please downgrade to 1.x for version 3 
For more details, please checkout the schema http://bucklescript.github.io/bucklescript/docson/#build-schema.json
>>>> Start compiling 
```

We already changed the `react-jsx` so why is it complaining? I had not seen this in a while so I had to jump back into the absolutely essential [`reasonml-discord`](https://discord.gg/reasonml) channel and search for it.

This has something to do with the version of `reason-react` we are using.

I know the solution is to add the latest version of `reason-react` but I'm mildly conflicted about whether I should handle the next line in the docs first.

> Update places where you use DOM refs (whether use React.createRef or React.useRef above your components).

I just searched for `useRef` and `createRef` in the project and found nothing so I'm just going to go ahead and install `reason-react@latest`.

```sh
npm i reason-react@latest
```

Didn't work:

```sh
~/Github/old-code-update2 updating*
❯ yarn start               
yarn run v1.22.4
$ bsb -make-world -w
File "bsconfig.json", line 5:
Error: JSX version 3 is deprecated, please downgrade to 1.x for version 3 
For more details, please checkout the schema http://bucklescript.github.io/bucklescript/docson/#build-schema.json
>>>> Start compiling 
```

Then I see:

```json
"bs-platform": "^4.0.7",
```

in `package.json` and realise we have to update that too.


Run `npm i bs-platform@latest` and we are back in business:

```sh
~/Github/old-code-update2 updating*
❯ yarn start              
yarn run v1.22.4
$ bsb -make-world -w
[37/37] Building src/ReactDOMRe.cmj
[15/15] Building src/Json.cmj
[8/8] Building src/Css.cmj
[5/5] Building src/jest.cmj
[14/14] Building src/DomTestingLibrary.cmj
[5/5] Building src/ReactTestingLibrary.cmj
>>>> Start compiling 
```

# Working Through Errors

The first error we see is knuckleheadish: `Error: Unbound module ReactCompat`.

When we installed the two libs, `reason-react-compat` and `reason-react-update` I forgot to add them to `bsconfig.json`. I used to have a script in my dotfiles that handled this, then I accidently deleted them. And now thanks to [learning in public](https://www.swyx.io/writing/learn-in-public/), I figured I should go ahead and figure it out again so you can use it too.

```sh
# script to add dependency to `packag.json.dependecies` and `bsconfig.[bs-dependencies]`
function _add_bs_dependency(){

  NEWDEP=$1
  npm install $NEWDEP

  $(cat bsconfig.json | jq --arg NEWDEP $NEWDEP -r '.["bs-dependencies"] 
 += [$NEWDEP]' | sponge bsconfig.json)

  cat bsconfig.json | jq '.["bs-dependencies"]'
  echo ✨${NEWDEP} added to bs-dependencies ✨
}
```

I am so happy to have this script back. One command to install a `bs-dependency`.

Stick that in your dotfiles and run `addbs reason-react-compat` and `addbs reason-react-update`.

You should get back:

```sh
❯ addbs reason-react-update
[
  "reason-react",
  "@glennsl/bs-json",
  "bs-css",
  "reason-react-compat",
  "reason-react-update"
]
✨reason-react-update added to bs-dependencies ✨
```

I should really figure out how to make the script take multiples args...

## ReasonReact.Compat

After restarting the project we should be getting a bunch of errors referrencing

```sh
  ReactCompat.useRecordApi({
    ...component,
```

We must hit the [`reason-react-compat docs`](
https://github.com/bloodyowl/reason-react-compat#stateless-components) here. There is a path to upgrading so lets follow it. We need to change all instances of `...component,` to `...ReactCompat.component`. Wait, those are strings! I wonder if [`FastReplaceString`](https://github.com/IwanKaramazow/FastReplaceString) can handle it. Better yet, I just remembered I have `replace` script. Let's try it.

We could try running:

```sh
# outputs just list of places wher are string shows up and pipe it to faststring replace
grep -rnwl 'src' -e '...component'  | fastreplacestring.exe "...component" "...ReactCompat.component"
```

But it needs some tweaking to work.

This is the `replace` script:

```sh
#!/bin/sh
#
# Find and replace by a given list of files.
#
# replace foo bar **/*.ml
# https://thoughtbot.com/blog/sed-102-replace-in-place

find_this="$1"
shift
replace_with="$1"
shift

if command -v rg &>/dev/null ; then
  items=$(rg -l --color never "$find_this" "$@")
else
  items=$(ag -l --nocolor "$find_this" "$@")
fi

temp="${TMPDIR:-/tmp}/replace_temp_file.$$"
IFS=$'\n'
for item in $items; do
  sed "s/$find_this/$replace_with/g" "$item" > "$temp" && mv "$temp" "$item"
done
```

Running `replace "...component" "...ReactCompat.component"` works fantastically.


Well that's it for now, folks. I can't promise I will finish this update because I got what I needed from it.

This has been [learning in public](https://www.swyx.io/writing/learn-in-public/).