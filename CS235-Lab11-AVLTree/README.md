### Lab 11: AVL Tree

THIS lab was a pain in the butt. It's basically the BST lab (not too bad) BUT it auto-balances itself. The textbook was entirely unhelpful, and it went throught a LOT of work just so you wouldn't have a balance datamember of the Node. I ended up just saying forget that, and added it so that each node keeps track of it's own balance. The other problem I ran into was getting the parent of a node. That was another thing that I ended up doing something pretty gimmicky, I made a function that given a node, will recurse down to the node, and then return the node before it get to the target node (its parent). This was an easy (albeit not super efficient way) of getting the parent of a node, which is super important for removal and rebalancing the tree.

I tried to get my dad to help with this lab, but it was very tedious for both of us to be working on it on the same computer, so he forked the project and we worked on it seperately to see what we could do on our own before coming together to discuss. I ended up just completely finishing the lab by myself before he did. His code was probably more efficient than mine in the end (though he never finished so we don't know for sure) but mine took less time to code which was more important for this lab.

It was well worth the time spent, however, because it basically nullified half of the final exam that I was pretty nervous for. After doing this lab, I could have gotten less than 30/100 on the final and still kept an A in the class. Time well spent.



<br />
Autograder:  40.0 / (40.0)
<br />
Peer Review: None for this lab.
