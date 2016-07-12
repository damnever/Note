# -*- coding: utf-8 -*-

#
# https://leetcode.com/problems/design-twitter/
##
# Your Twitter object will be instantiated and called as such:
# obj = Twitter()
# obj.postTweet(userId,tweetId)
# param_2 = obj.getNewsFeed(userId)
# obj.follow(followerId,followeeId)
# obj.unfollow(followerId,followeeId)

from itertools import count
import heapq


class Twitter(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._timer = count()
        # dict is fast than defaultdict
        self._relationships = dict()
        self._tweets = dict()

    def postTweet(self, userId, tweetId):
        """
        Compose a new tweet.
        :type userId: int
        :type tweetId: int
        :rtype: void
        """
        tweet = (next(self._timer), tweetId)
        if userId not in self._tweets:
            self._tweets[userId] = [tweet]
        else:
            self._tweets[userId].insert(0, tweet)

    def getNewsFeed(self, userId, push=heapq.heappush,
                    pushpop=heapq.heappushpop, pop=heapq.heappop):
        """
        Retrieve the 10 most recent tweet ids in the user's news feed.
        Each item in the news feed must be posted by users who the user
        followed or by the user herself. Tweets must be ordered from
        most recent to least recent.
        :type userId: int
        :rtype: List[int]
        """
        feeds = []
        count = 0
        for user in (self._relationships.get(userId, set()) | {userId}):
            for tweet in self._tweets.get(user, []):
                if count < 10:
                    push(feeds, tweet)
                    count += 1
                elif tweet[0] < feeds[0][0]:
                    break
                else:
                    pushpop(feeds, tweet)
        return [pop(feeds)[1] for _ in xrange(count)][::-1]


    def follow(self, followerId, followeeId):
        """
        Follower follows a followee. If the operation is invalid,
        it should be a no-op.
        :type followerId: int
        :type followeeId: int
        :rtype: void
        """
        if followerId not in self._relationships:
            self._relationships[followerId] = {followeeId}
        else:
            self._relationships[followerId].add(followeeId)

    def unfollow(self, followerId, followeeId):
        """
        Follower unfollows a followee. If the operation is invalid,
        it should be a no-op.
        :type followerId: int
        :type followeeId: int
        :rtype: void
        """
        self._relationships.get(followerId, set()).discard(followeeId)


if __name__ == '__main__':
    twitter = Twitter()
    twitter.postTweet(1, 5)
    print(twitter.getNewsFeed(1))
    assert twitter.getNewsFeed(1) == [5]

    twitter.follow(1, 2)
    twitter.postTweet(2, 6)
    print(twitter.getNewsFeed(1))
    assert twitter.getNewsFeed(1) == [6, 5]

    twitter.unfollow(1, 2)
    print(twitter.getNewsFeed(1))
    assert twitter.getNewsFeed(1) == [5]
