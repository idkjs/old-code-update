# Updating with [bloodyowl](https://github.com/bloodyowl/upgrade-reason-react-esy)

Let follow the [README](https://github.com/bloodyowl/upgrade-reason-react-esy#README.md) instructions.

1. `npm i bloodyowl-upgrade-reason-react`.

Trying to install fails. I am guessing its because of some `package-lock.json` dependency.

Lets `rm package-lock.json` to get rid of the old deps interfereing. I am also going to get rid of the `node`,`grpc@1.13.1`, `node-pre-grp` and `bs-platform@4.0.7` files since, first, why are they there?, and second,not the point of what we are doing here.

Lets run:

```sh
rm package-lock.json node grpc@1.13.1 node-pre-grp bs-platform@4.0.7
``` 

And try installing again, `npm install`. This takes a while because it has to build `grpc@1.13.1`. Installing fails again because the project requires `node 10.x` listed in `engines` in `package.json`. I am using `fnm` so I will add the correct version with `fnm install 10` the run `fnm use 10`. 

Run `npm install` again and it works.

Try installing the upgrade package again:

```sh
> npm i bloodyowl-upgrade-reason-react
```

Next we will run `find src -name "*.re" | yarn Upgrade` from the docs.

Here is the output if you run the command, but don't just yet:

```sh
~/Github/form-builder-reasonml updating* 21s
❯ find src -name "*.re" | yarn Upgrade
yarn run v1.22.4
$ /Users/mandalarian/Github/form-builder-reasonml/node_modules/.bin/Upgrade
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

~/Github/form-builder-reasonml updating*
❯ 
```
Let's run it and push the output to a file:

```sh
❯ find src -name "*.re" | yarn Upgrade > edits.cfg
```

It should look something like:

```txt
yarn run v1.22.4
$ /Github/form-builder-reasonml/node_modules/.bin/Upgrade
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

# Updating Strings

> If you've alias ReasonReact to React, search and replace it back to ReasonReact. 

> # Search and replace: 

> ReasonReact.Update to Update 

> ReasonReact.UpdateWithSideEffects to UpdateWithSideEffects 

> ReasonReact.SideEffects to SideEffects 

> ReasonReact.NoUpdate to NoUpdate

This seems a bit error prone to redo these steps every time I am up in some random old repo so I wrote this little hack using this awesome random library I came across in my random `reason` project meandering. Its called [FastReplaceString](https://github.com/IwanKaramazow/FastReplaceString) by some hacker named [Iwan Karamazow](https://github.com/IwanKaramazow) who seems to have been active in the early `reason` days. Thanks, Iwan!

Let's install his utiility:

```sh
npm i -D IwanKaramazow/FastReplaceString
```

Lets create a script call `reasonreactupdate.sh` and put this in it:

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

So what are we doing? Instead of searching for each set of string in our editor we will iterate over tuples of the edits we want to make calling each variation of what [bloodyowl](https://www.twitter.com/@bloodyowl) wants us to do with `fastreplacestring`.

Just for for fun, in your are in a situation where you have aliased the `ReasonReact` as `React` we can just run both changes on all the affected files.

```sh
# reactupdate.sh
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
~/Github/form-builder-reasonml updating*
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
~/Github/form-builder-reasonml updating*
❯ 
```

## Install reason-react from [this](https://github.com/bloodyowl/reason-react) fork's master branch

Now we need to install a specific version of `reason-react` as indicated by the docs and to addition `@bloodyowl` libs,`reason-react-update` and `reason-react-compat` for using the old `ReasonReact` api in your project.
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

I just searched for `useRef` and `createRef` in the project and found nothing so just going to go ahead and install `reason-react@latest`.

```sh
npm i reason-react@latest
```

Didn't work:

```sh
~/Github/form-builder-reasonml2 updating*
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
~/Github/form-builder-reasonml2 updating*
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

The first error we see is stupid, `Error: Unbound module ReactCompat`.

When we install the two lib, `reason-react-compat` and `reason-react-updates` we forgot to add them to `bsconfig.json`. I used to have a script in my dotfiles that handled this, then I accidently deleted them. And now thanks [learning in public](https://www.swyx.io/writing/learn-in-public/), I figured I should go ahead and figure it out again so you can use it too.

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
https://github.com/bloodyowl/reason-react-compat#stateless-components) here. There is a path to upgrading so lets follow it. We need to change all instances of `...component,` to `...component`. Wait, those are strings! I wonder if [`FastReplaceString`](https://github.com/IwanKaramazow/FastReplaceString) can handle it. Better yet, I just remembered I have `replace` script. Let's try it.

We could try running:

```sh
# outputs just list of places wher are string shows up and pipe it to faststring replace
grep -rnwl 'src' -e '...component'  | fastreplacestring.exe "...component" "...component"
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

Running `replace "...component" "...component"` works fantastically.
