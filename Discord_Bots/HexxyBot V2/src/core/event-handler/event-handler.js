
const logger = require('../utils/logger');
const { ActivityType } = require('discord.js');
//...
            await client.user.setActivity(status, { type: ActivityType.Playing });
         //...
         
      events.forEach((e) => client.on(e[0], eventdata => e[1](client, eventdata)));