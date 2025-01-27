# Problem 

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]

 

Constraints:

    2 <= nums.length <= 104
    -109 <= nums[i] <= 109
    -109 <= target <= 109
    Only one valid answer exists.

 
Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?

# Thinking

Always nice to think in terms of how many list passes you might need to do this
On a single list pass you might have enough information since you know oh my goodness yeah you know what the other number would have to be
so you could just check if you've seen it yet

If you have some like O(1) map for have seen the number (but ig space inefficient) then you're good
So on a pass you just go ok I see this number, what would we have to have seen already to 

Also naive solution probs of just for every number adding every other number to it and compare like that would be easy as right
Simple O(n^2) there

But ya the faster approach would be to like use some mapping structure to check if we have seen the number we would need yet
One question would be what if the number is further along the list but Ig that this solution would be completely symmetrical so that shouldn't
be such an issue

Main issue would probs be an efficient mapping structure but I think the problem constraints r handy here since we have -109 <= nums[i] <= 109 oh wait no that was a copy
paste error that says 10^9. Ok there's the issue here I think is that what mapping structure could actually store 2 * 10^9 elements efficiently
In the worst case ig there is like 100000 collisions or I suppose exactly how many collisions would there be it's worth confirming
At most we have 10^4 elements to check, so ig depending on the details of the algorithm at worst we have the misfortune of 10^4 collisions.

Depends completely at this point on the efficiency of map for this solution. Are there solutions that do not rely on this? Or could just begin to research the efficiency of rust built in mapping
functions

I am fixating a little on the idea that a solution should for each number check if we already know the problem can be solved. I.e. whenever we see a number we can somehow instantly go oh yeah this index would work. 
I feel like this is basically the right idea but can be do so more quickly? Like this is essentially a question about how we parse numbers that we see + how we store them.
Most naive O(n^2) approach would be to yeah just put them into a "seen" list which we iterate through basically, or just use the rest of the list which is effectively the same thing but without duplicating the memory etc
    Which is I suppose going to take n(n-1) + (n-1)(n-2) + (n-2)(n-3) + ... iterations which is still O(n^2) comparisons

The other structure I have entertained for storing "already seen" information is a map but yeah that may be absolutely best speed wise except we can't store it efficiently enough
Also worth entertaining briefly using a bitmap for seen / not seen but that is not enough information - we need to return the correct indices not just whether it is possible.
Therefore we would need to store an unsigned int up to 10^4 so ya na not gonna fly unless we have like a bitmap to check if its possible and then a lookup
table which we know will never not be occupied for the desired index but idk if that speeds things up any more.

The only other really sort of structure I'm aware of is like a tree of some sort. Could a tree be used?
Ig the idea here is about wheter size comparisons (surely the only meaningful comparison here) could be useful. Let's say target is 21 and we encounter 8.

What sort of decision tree could help? 
I suppose we know we can rule out any numbers > (21-8 = 13) since these will be too large. If we have 13 that would be correct. ACtually what I think I'm really getting at is
that if the list was sorted this problem would be like O(n * log_2n) since at each index we could basically do a binary search of either the top half or bottom half of the list depending on whether
index[i] </> target/2.

So as long as we are populating a binary tree of the numbers as we iterate, both populating and iterating through a binary tree is O(log_2 n), there's no risk of collisions and we don't have issues with memory since at most we are storing nums.length again. I think this is probably a good solution - for each index (O(n) we would do a binary tree insertion and traversal right? Let's just flesh this out a litle bit more because that specific example I did was a binary tree for each nums[i] which would involve creating a whole tree for each nums[i] which is no better than loopin through the whole list in fact is much worse.

Let's step through it again. Target is 21, we find 8, we have a partially completed tree T.

Oh but we know we are looking for 13. So then we just need to see if 13 is in the tree (and also add 8 to the tree)
So this is easy. We also know these would be on different halves of the tree so like high key if we had access to some threading or sth we know these could not collide with each other.

We would basically (ideally simultaneously since again these do not touch the same branch necessarily) also note we could have duplicate numbers ig we would then store like a list of indices
    there would probs be some choice issue here if we could have multiple results but just one result means I can ignore the case where like 4 occurences of the same target/2 occur or sth

Oh god I would have to do all the rebalancing though because "starts on the other half of the tree" assumes that we instantly begin at the midpoint which is ofc not true in general.
I think that spoils my idea of perfect multithreading between the insertion and iteration since yeah the whole tree structure would be changing.

ACtually therefore let's step through a whole solution instead of just starting with T

At this point high key I probs have a good enough idea to start coding but ah fuck it may as well identify any pitfalls now won't take a second anyway

Say nums is idk [19, 8, 3, 14, 6, 6, 9, 18] and target is 21 may as well see the tree be repopulated many times before actually getting the solution of 18, 3

1. i = 0, T.root = 19 (taking the value in place of the index since here they are like equivalent we just add the extra information)
2. i = 1, encounter 8, we know that 8 < 19 so naively we just put 8 at 19.left but in this worst case we end up back at O(n^2) if list is in like descending order (or ascending)
    so instead what ig we know that wait hang on this is not as easy as I kinda imagined. Ideally what is in the middle not 13 ideally like (21 - 10^-9) / 2 is in the middle right since that's actually the lowest bound.
    So I think we know we need to rebalance if the new item is closer to the "middle" than the top element oh wait I have also implicitly assumed that nums[i] < target. But actually both are just less than 10^9 (MAX). 
    What actually is this criteria? Cuz my instinct is to say that now we have like two cases for whether we encounter nums[i] > target or not. I suppose also no reason to not encounter nums[i] == target and then we would be looking for nums[j] == 0

Does the problem actually change with this realisation? Let's say we encounter the number 25, then we would want to see if we have -4 in the tree. We still will basically ideally want a balanced tree, so the problem is actually not really different but it is a bit less specific - we really only want a balanced tree at all times, it doesn't need to be balanced towards the "middle" because that idea doesn't really make a lot of sense anymore.

So this I think is then just a normal B-tree problem, where we essentially want a sorted structure that allows for fast lookup of already found numbers. 
That's just the fastest way to do that if maps aren't an option. 

Are we certain this is the right approach? The question has become how do I most efficiently find a specific number while adding a new number also. I think so...
In my head I would love to see some solution that doesn't require direct knowledge of every passed index value (alongisde whatever associated lookup).
What could that look like? There would have to be some metric that is smaller than a list of every thing that still allows us to get any index already or sth,......
Nah we lose information - I think we need that information, because for any new index it could be that any of the previously seen indices is correct.

Unless we can perform some calculation that yields the correct answer after traversing the entire list. I don't know what that calculation could be. Maybe a number theorist would know.

I think without stumbling upon some correct metric like that we have to just proceed with the approach that the question is essentially about efficiently storing and searching an "already-seen" structure which we populate and traverse for each newly seen element. The answer to which is some O(1) map if possible but probs not here so next best is a tree.

So at absolute worst we always have to do a rebalance and then a full tree reversal at each step I think these are all log_2(n). ACtually I can't quite remember ngl been a fat sec since I've written a rebalance. I think if we do it at every step along the way you only have to perform one tree rotation at the point you realise the balance is off. Fuck I would really need to like remember what this looks like draw some pictures the whole thing.

I remember though there are only a few super limited cases.
I also remember that this is not a particularly easy structure to implement in Rust where we don't have like pointers and all the memory ownership issues. High key so tempted to transition it to c++... 
Might google around a bit to see what b tree implementations end up looking like in RUst I just don't know the language well enough to not do that.

Rust implements a btree map so ig if I can just use that which ofc I can because here we are then we're good.

Probs (def) a good exercise to implement some details myself... ik how to do the logic for that (or I could figure it out again quickly) and could implement it using references + smart pointers in C++ (not raw ew gross what is this C99?!?)
    But ya wrestling w the memory ownership in rust sounds daunting.
Rust std::collections::BTreeMap (or whatever its actually called) also supports Entries which solves the whole find +\or insert problem ig yea actually this solution would be quite simple using this collection
And if I implemented the functionality myself then I would just do that and provide myself a similarly helpful interface. 

Also worth mentioning that if I had a language like cuda with real vectorisation this would be O(n) because we could just iterate along the list and perform the sum - target and if zero then store the index with the list item. Then a second iteration along the list would just check if any of the threads / cuda cores or whatever created an index pair. 
That would actually be really fun to try to implement ngl and actually that is fully parallelisable even without a proper vector thing but like ig the synching wouldn't actually deliver any improvements without true parallelism.

Actually is that true? If we make a thread for each array item they would all just require a readonly copy of the array itself in fact the array itself as a data structure wouldn't ever need to change.....
Ofc like we need all the threads to actually be running at least somewhat in parallel otherwise we're just at O(n^2) and launching like 10^4 true threads is probably not viable. A shader however........

This would actually be such a fun like intro shader programming task I should so do that ngl. But let's do this problme first maybe we do it a couple of ways:

1. The rust solution just using a btreemap 
2. C++ solution without any parallelisation
3. Like some CUDA shader implementation or sth that I won't be able to run cuz I don't have a gpu lol

## A couple days later

Today (next train trip lol) implemented the rust version which was accepted by leetcode no real shock there.
Might have a stab now at the C++ versions. Will experiment also I think with a parameterised CMake build that optionally uses the OpenGL solution or doesn't depending maybe on like a flag when cmake is invoked.

Also worth noting that the rust definitely felt unnatural - need to practice it a bit more with a couple more problems I think before I should feel happy to try out another language.
