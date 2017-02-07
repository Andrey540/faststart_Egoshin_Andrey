using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Web.Http;
using Newtonsoft.Json;

namespace SelfHostingWebApplication
{
    public class UserController : ApiController
    {
        private int m_maxUserId;
        private const string MAX_USER_ID_KEY = "max_uer_id";
        private const string USERS_KEY_PREFIX = "users_";

        public UserController()
        {
            string maxUserIdString = RedisDBManager.GetDatabase().StringGet(MAX_USER_ID_KEY);
            try
            {
                this.m_maxUserId = Convert.ToInt32(maxUserIdString, 10);
            }
            catch (OverflowException)
            {
                this.m_maxUserId = 0;
            }
        }

        public User GetUserById(int id)
        {
            var redisObject = RedisDBManager.GetDatabase().StringGet(USERS_KEY_PREFIX + id.ToString());
            if (redisObject.HasValue)
            {
                return JsonConvert.DeserializeObject<User>(
                    redisObject,
                    new JsonSerializerSettings {
                        ReferenceLoopHandling = ReferenceLoopHandling.Serialize,
                        PreserveReferencesHandling = PreserveReferencesHandling.Objects
                    });
            }
            else
            {
                return null;
            }
        }

        public int PutUser(string firstName, string lastName, string email)
        {
            ++this.m_maxUserId;
            string stringId = this.m_maxUserId.ToString();
            RedisDBManager.GetDatabase().StringSet(MAX_USER_ID_KEY, stringId);
            User user = new User() { ID = this.m_maxUserId, FirstName = firstName, LastName = lastName, Email = email };
            RedisDBManager.GetDatabase().StringSet(USERS_KEY_PREFIX + stringId, JsonConvert.SerializeObject(
                user,
                Formatting.Indented,
                new JsonSerializerSettings {
                    ReferenceLoopHandling = ReferenceLoopHandling.Serialize,
                    PreserveReferencesHandling = PreserveReferencesHandling.Objects
                }));
            return this.m_maxUserId;
        }
    }
}
