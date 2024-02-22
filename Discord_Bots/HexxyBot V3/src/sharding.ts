import { ShardingManager } from 'discord.js';
import { Token } from './config/botConfig';
import * as Logger from './core/utils/logger';

const manager = new ShardingManager('./build/bot.js', { token:Token });

manager.on('shardCreate', (shard) => Logger.info(`Launched shard n° ${shard.id}`));
manager.spawn();
